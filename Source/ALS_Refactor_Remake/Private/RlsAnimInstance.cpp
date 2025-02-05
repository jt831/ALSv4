// Fill out your copyright notice in the Description page of Project Settings.

#include "RlsAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "RlsCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Utility/RlsConstants.h"

void URlsAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ARlsCharacter>(GetOwningActor());
}

void URlsAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	ensure(Character);
	ensure(Settings);
}

void URlsAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (!IsValid(Character) || !IsValid(Settings)) return;
	
	UpdateInfoFromCharacter();
	UpdateBaseValues(DeltaSeconds);
	UpdateStandingMovement();
	UpdateGroundedMovement(DeltaSeconds);
	UpdateControlRigInput();
	UpdateInAirOnGameThread();
	bIsFirstUpdate = false;
}

void URlsAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	/*
	 * 将获取曲线值放在线程安全更新中
	 */
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	if (!IsValid(Character) || !IsValid(Settings)) return;
	
	UpdatePoseState();
}

void URlsAnimInstance::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();

	if (!IsValid(Character) || !IsValid(Settings)) return;

	PlayQueuedTransition();
	StopQueuedTransition();
}


void URlsAnimInstance::UpdateInfoFromCharacter()
{
	/*
	 * 单纯用于接收来自角色的信息
	 */
	RotationMode = Character->GetRotationMode();
	Gait = Character->GetGait();
	LocomotionMode = Character->GetLocomotionMode();
	
	const FRlsLocomotionValues LocomotionValues = Character->GetLocomotionValues();
	LocomotionBaseValues.Speed = LocomotionValues.Speed2D;
	LocomotionBaseValues.Velocity = LocomotionValues.Velocity;
	LocomotionBaseValues.bMoving = LocomotionValues.bHasVelocity;
	LocomotionBaseValues.Acceleration = LocomotionValues.Acceleration;
	LocomotionBaseValues.bHasAcceleration = LocomotionValues.bHasAcceleration;
	LocomotionBaseValues.bHasInput = LocomotionValues.bHasInput;
	LocomotionBaseValues.Location = Character->GetActorLocation();

	auto* Capsule = Character->GetCapsuleComponent();
	LocomotionBaseValues.CapsuleRadius = Capsule->GetScaledCapsuleRadius();
	LocomotionBaseValues.CapsuleHalfHeight = Capsule->GetScaledCapsuleHalfHeight();
}

void URlsAnimInstance::UpdateGroundedMovement(float DeltaTime)
{
	// 更新VelocityBlend
	FVector LocalVelocity = GetLocalVelocity();
	if (LocalVelocity.Normalize() && LocalVelocity.Length() > UE_SMALL_NUMBER)
	{
		LocalVelocity /= FMath::Abs(LocalVelocity.X)+FMath::Abs(LocalVelocity.Y)+FMath::Abs(LocalVelocity.Z);
	}
	float InterpSpeed = Settings->Grounded.VelocityBlendInterpSpeed;
	
	float ForwardTarget = FMath::Clamp(LocalVelocity.X, 0., 1.);
	GroundedState.VelocityBlend.ForwardAmount = FMath::FInterpTo(GroundedState.VelocityBlend.ForwardAmount, ForwardTarget, DeltaTime, InterpSpeed);
	float BackwardTarget = FMath::Abs(FMath::Clamp(LocalVelocity.X, -1., 0.));
	GroundedState.VelocityBlend.BackwardAmount = FMath::FInterpTo(GroundedState.VelocityBlend.BackwardAmount, BackwardTarget, DeltaTime, InterpSpeed);
	float LeftTarget = FMath::Abs(FMath::Clamp(LocalVelocity.Y, -1., 0.));
	GroundedState.VelocityBlend.LeftAmount = FMath::FInterpTo(GroundedState.VelocityBlend.LeftAmount, LeftTarget, DeltaTime, InterpSpeed);
	float RightTarget = FMath::Clamp(LocalVelocity.Y, 0., 1.);
	GroundedState.VelocityBlend.RightAmount = FMath::FInterpTo(GroundedState.VelocityBlend.RightAmount, RightTarget, DeltaTime, InterpSpeed);

	// 更新MovementDirection
	const FRotator Velocity_RotateFromXVector = UKismetMathLibrary::Conv_VectorToRotator(LocomotionBaseValues.Velocity);
	const FRotator ControlRotator = Character->GetControlRotation();
	UKismetMathLibrary::NormalizedDeltaRotator(Velocity_RotateFromXVector, ControlRotator);
	const float DeltaAngle_VC = FMath::UnwindDegrees(Velocity_RotateFromXVector.Yaw - ControlRotator.Yaw);
	
	if (RotationMode == RlsRotationModeTags::VelocityDirection ||
		Gait == RlsGaitTags::Sprinting)
	{
		GroundedState.MovementDirection = ERlsMovementDirection::Forward;
	}
	else
	{
		const float AngleThreshold = Settings->Grounded.MovementDirectionThreshold;
		
		if (DeltaAngle_VC < AngleThreshold && DeltaAngle_VC > -AngleThreshold)
		{
			GroundedState.MovementDirection = ERlsMovementDirection::Forward;
		}
		else if (DeltaAngle_VC > AngleThreshold && DeltaAngle_VC < 180.f - AngleThreshold)
		{
			GroundedState.MovementDirection = ERlsMovementDirection::Right;
		}
		else if (DeltaAngle_VC < -AngleThreshold && DeltaAngle_VC > -180.f + AngleThreshold)
		{
			GroundedState.MovementDirection = ERlsMovementDirection::Left;
		}
		else
		{
			GroundedState.MovementDirection = ERlsMovementDirection::Backward;
		}
	}

	// 更新RotationYawOffset
	if (IsValid(Settings->Grounded.RotationYawOffset_FB) &&
		IsValid(Settings->Grounded.RotationYawOffset_L) &&
		IsValid(Settings->Grounded.RotationYawOffset_R))
	{
		float RotationYawOffset_FB = Settings->Grounded.RotationYawOffset_FB->GetFloatValue(DeltaAngle_VC);
		float RotationYawOffset_L = Settings->Grounded.RotationYawOffset_L->GetFloatValue(DeltaAngle_VC);
		float RotationYawOffset_R = Settings->Grounded.RotationYawOffset_R->GetFloatValue(DeltaAngle_VC);
		GroundedState.RotationYawOffsets.ForwardAngle = RotationYawOffset_FB;
		GroundedState.RotationYawOffsets.BackwardAngle = RotationYawOffset_FB;
		GroundedState.RotationYawOffsets.LeftAngle = RotationYawOffset_L;
		GroundedState.RotationYawOffsets.RightAngle = RotationYawOffset_R;
	}
}

void URlsAnimInstance::UpdateInAirOnGameThread()
{
	check(IsInGameThread())

	//UE_LOG(LogTemp, Warning, TEXT("%hhu"), InAirState.bDesiredJumped);
	InAirState.bJumped = InAirState.bJumped || InAirState.bDesiredJumped;
	InAirState.bDesiredJumped = false;
}

void URlsAnimInstance::UpdateStandingMovement()
{
	// 更新StrideBlendAmount
	StandingState.StrideBlendAmount =
		FMath::Lerp(
			Settings->Grounded.Standing.StrideBlendAmountWalkCurve->GetFloatValue(LocomotionBaseValues.Speed),
			Settings->Grounded.Standing.StrideBlendAmountRunCurve->GetFloatValue(LocomotionBaseValues.Speed),
			PoseState.UnweightedGaitRunningAmount);
	
	// 更新WalkRunBlendAmount
	StandingState.WalkRunBlendAmount =
		Gait == RlsGaitTags::Walking ? 0.f : 1.f;

	// 更新PlayRate
	const float PlayRatePart1 =
		FMath::Lerp(
			LocomotionBaseValues.Speed / Settings->Grounded.Standing.AnimatedWalkSpeed,
			LocomotionBaseValues.Speed / Settings->Grounded.Standing.AnimatedRunSpeed,
			PoseState.UnweightedGaitRunningAmount
			);
	const float PlayRatePart2 =
		FMath::Lerp(
			PlayRatePart1,
			LocomotionBaseValues.Speed / Settings->Grounded.Standing.AnimatedSprintSpeed,
			PoseState.UnweightedGaitSprintingAmount
			);

	const float PlayRatePart3 = PlayRatePart2 / StandingState.StrideBlendAmount;
	StandingState.PlayRate = FMath::Clamp(PlayRatePart3, UE_SMALL_NUMBER, 3.0f);

	StandingState.SprintBlockAmount = GetCurveValue(URlsConstants::SprintBlockCurveName());
}

void URlsAnimInstance::UpdatePoseState()
{
	/*
	 * 获取动画曲线值并进行一些处理
	 */
	PoseState.GroundedAmount = GetCurveValue(URlsConstants::PoseGroundedCurveName());
	PoseState.InAirAmount = GetCurveValue(URlsConstants::PoseInAirCurveName());
	
	PoseState.StandingAmount = GetCurveValue(URlsConstants::PoseStandingCurveName());
	PoseState.CrouchingAmount = GetCurveValue(URlsConstants::PoseCrouchingCurveName());
	
	PoseState.MovingAmount = GetCurveValue(URlsConstants::PoseMovingCurveName());

	PoseState.GaitAmount = FMath::Clamp(GetCurveValue(URlsConstants::PoseGaitCurveName()), 0.0f, 3.0f);
	PoseState.GaitWalkingAmount = FMath::Clamp(PoseState.GaitAmount, 0.f, 1.f);
	PoseState.GaitRunningAmount = FMath::Clamp(PoseState.GaitAmount-1, 0.f, 1.f);
	PoseState.GaitSprintingAmount = FMath::Clamp(PoseState.GaitAmount-2, 0.f, 1.f);

	PoseState.UnweightedGaitAmount = PoseState.GroundedAmount > UE_SMALL_NUMBER
										 ? PoseState.GaitAmount / PoseState.GroundedAmount
										 : PoseState.GaitAmount;
	PoseState.UnweightedGaitWalkingAmount =  FMath::Clamp(PoseState.UnweightedGaitAmount, 0.f, 1.f);
	PoseState.UnweightedGaitRunningAmount = FMath::Clamp(PoseState.UnweightedGaitAmount-1, 0.f, 1.f);
	PoseState.UnweightedGaitSprintingAmount = FMath::Clamp(PoseState.UnweightedGaitAmount-2, 0.f, 1.f);

	// 更新FeetCross曲线值
	GroundedState.FeetCrossCurveAmount = GetCurveValue(URlsConstants::FeetCrossingCurveName());
	GroundedState.FootPlantedCurveAmount = GetCurveValue(URlsConstants::FootPlantedCurveName());
}

void URlsAnimInstance::UpdateBaseValues(float DeltaTime)
{
	LocomotionBaseValues.DeltaDistance = (Character->GetActorLocation() - LocomotionBaseValues.WorldLocation).Length();
	LocomotionBaseValues.WorldLocation = Character->GetActorLocation();
	LocomotionBaseValues.DistanceSpeed = LocomotionBaseValues.DeltaDistance / DeltaTime;
	if (bIsFirstUpdate)
	{
		LocomotionBaseValues.DeltaDistance = 0.f;
		LocomotionBaseValues.DistanceSpeed = 0.f;
	}
}


FVector URlsAnimInstance::GetLocalVelocity() const
{
	return Character->GetActorRotation().UnrotateVector(LocomotionBaseValues.Velocity);
}

UCharacterMovementComponent* URlsAnimInstance::GetCharacterMovementComponent() const
{
	return Cast<UCharacterMovementComponent>(Character->GetMovementComponent());
}

void URlsAnimInstance::SetHipsDirection(ERlsHipDirection HipDirection)
{
	GroundedState.HipDirection = HipDirection;
}

void URlsAnimInstance::PlayTransition(UAnimSequenceBase* Sequence, float BlendInTime, float BlendOutTime,
	float StartTime, float PlayRate)
{
	GroundedState.TransitionInfo.BlendInTime = BlendInTime;
	GroundedState.TransitionInfo.BlendOutTime = BlendOutTime;
	GroundedState.TransitionInfo.StartTime = StartTime;
	GroundedState.TransitionInfo.PlayRate = PlayRate;
	GroundedState.TransitionInfo.Sequence = Sequence;
}

void URlsAnimInstance::StopTransition(float BlendOutDuration)
{
	GroundedState.TransitionInfo.bStopTransitionQueued = true;
	GroundedState.TransitionInfo.StopBlendOutTime = BlendOutDuration;
}

void URlsAnimInstance::PlayQueuedTransition()
{
	check(IsInGameThread())

	if (!IsValid(GroundedState.TransitionInfo.Sequence) || GroundedState.TransitionInfo.bStopTransitionQueued) return;
	
	PlaySlotAnimationAsDynamicMontage(GroundedState.TransitionInfo.Sequence, URlsConstants::FootStopSlotName(),
		GroundedState.TransitionInfo.BlendInTime, GroundedState.TransitionInfo.BlendOutTime,
		GroundedState.TransitionInfo.PlayRate,
		1, 0, GroundedState.TransitionInfo.StartTime);
	
	GroundedState.TransitionInfo.Sequence = nullptr;
	GroundedState.TransitionInfo.BlendInTime = 0.;
	GroundedState.TransitionInfo.BlendOutTime = 0.;
	GroundedState.TransitionInfo.StartTime = 0.;
	GroundedState.TransitionInfo.PlayRate = 1.;
}

void URlsAnimInstance::StopQueuedTransition()
{
	check(IsInGameThread())

	if (!GroundedState.TransitionInfo.bStopTransitionQueued) return;
	
	StopSlotAnimation(GroundedState.TransitionInfo.StopBlendOutTime, URlsConstants::FootStopSlotName());

	GroundedState.TransitionInfo.bStopTransitionQueued = false;
	GroundedState.TransitionInfo.StopBlendOutTime = 0.;

}

void URlsAnimInstance::UpdateInAir()
{
	if (!IsValid(Settings)) return;
	
	// 在动画蓝图中调用
	if (InAirState.bJumped)
	{
		InAirState.bJumped = false;
		InAirState.JumpPlayRate = FMath::Lerp(Settings->InAir.MinPlayRate, Settings->InAir.MaxPlayRate,
			FMath::Clamp(LocomotionBaseValues.Speed / Settings->InAir.PlayRateSpeed, 0., 1.));
	}

	UpdateGroundPrediction();
}

void URlsAnimInstance::UpdateGroundPrediction()
{
	const float VerticalSpeedThreshold = Settings->InAir.MinVerticalSpeed;
	const float MinVerticalSpeed = Settings->InAir.MinVerticalSpeed;
	const float MaxVerticalSpeed = Settings->InAir.MaxVerticalSpeed;
	const float MaxSweepDistance = Settings->InAir.MaxSweepDistance;
	const float MinSweepDistance = Settings->InAir.MinSweepDistance;
	float VerticalSpeed = abs(LocomotionBaseValues.Velocity.Z);
	
	// 如果速度过小，则不检测
	if (VerticalSpeed < VerticalSpeedThreshold) return;

	// 将下落速度映射到检测距离上去
	float SweepDistance = FMath::GetMappedRangeValueClamped(FFloatRange(MinVerticalSpeed, MaxVerticalSpeed),
		FFloatRange(MinSweepDistance, MaxSweepDistance), VerticalSpeed);
	float SweepVector = SweepDistance * LocomotionBaseValues.Velocity.Normalize();

	FVector SweepLocation = LocomotionBaseValues.Location;
	// 检测
	FHitResult Hit;
	GetWorld()->SweepSingleByChannel(Hit, SweepLocation, SweepLocation+SweepVector,
		FQuat::Identity, ECC_Visibility, FCollisionShape::MakeCapsule(LocomotionBaseValues.CapsuleRadius, LocomotionBaseValues.CapsuleHalfHeight));

	bool bGroundValid = Hit.IsValidBlockingHit();

	InAirState.GroundPredictionAmount = bGroundValid ? Settings->InAir.GroundPredictionAmountCurve->GetFloatValue(Hit.Time) : 0;
}

void URlsAnimInstance::UpdateControlRigInput()
{
	ControlRigInput.LeftFootIKWeight = GetCurveValue(URlsConstants::FootLeftIkCurveName());
	ControlRigInput.RightFootIKWeight = GetCurveValue(URlsConstants::FootRightIkCurveName());
	
	if (ControlRigInput.LeftFootIKWeight > 0.)
	{

		UpdateFootLockInfo(ControlRigInput.FootLockInfo.LeftFootLockWeight, ControlRigInput.FootLockInfo.LeftFootLocation,
			ControlRigInput.FootLockInfo.LeftFootRotation, URlsConstants::FootLeftLockCurveName(), URlsConstants::LeftFootIkName());
	}

	if (ControlRigInput.RightFootIKWeight > 0.)
	{
		UpdateFootLockInfo(ControlRigInput.FootLockInfo.RightFootLockWeight, ControlRigInput.FootLockInfo.RightFootLocation,
			ControlRigInput.FootLockInfo.RightFootRotation, URlsConstants::FootRightLockCurveName(), URlsConstants::RightFootIkName());
	}
}

void URlsAnimInstance::UpdateFootLockInfo(float& Alpha, FVector& Location, FRotator& Rotation, const FName& FootLockCurve, const FName& FootIkBone)
{
	float FootLockCurveValue = GetCurveValue(FootLockCurve);
	
	if (FootLockCurveValue > 0.99 || FootLockCurveValue < Alpha)
	{
		Alpha = FootLockCurveValue;
	}

	auto SkeletonMeshComp = GetOwningComponent();
	if (Alpha > 0.99)
	{
		FTransform IkBoneTrans = SkeletonMeshComp->GetSocketTransform(FootIkBone, RTS_Component);

		Location = IkBoneTrans.GetLocation();
		Rotation = IkBoneTrans.GetRotation().Rotator();
	}

	if (Alpha > 0.)
	{
		FVector DeltaDistance = SkeletonMeshComp->GetComponentRotation().UnrotateVector(LocomotionBaseValues.Velocity * GetDeltaSeconds());
		Location -= DeltaDistance;
	}
}
