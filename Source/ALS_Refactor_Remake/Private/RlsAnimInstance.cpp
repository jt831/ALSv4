// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/KismetMathLibrary.h"
#include "RlsAnimInstance.h"
#include "RlsCharacter.h"
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
	UpdateStandingMovement();
	UpdateGroundedMovement(DeltaSeconds);
}

void URlsAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	/*
	 * 将获取曲线值放在线程安全更新中
	 */
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	UpdatePoseState();
}


void URlsAnimInstance::UpdateInfoFromCharacter()
{
	/*
	 * 单纯用于接收来自角色的信息
	 */
	CharacterStates = Character->GetCharacterStates();
	
	const FRlsLocomotionValues LocomotionValues = Character->GetLocomotionValues();
	LocomotionBaseValues.Speed = LocomotionValues.Speed2D;
	LocomotionBaseValues.Velocity = LocomotionValues.Velocity;
	LocomotionBaseValues.bMoving = LocomotionValues.bHasVelocity;
	LocomotionBaseValues.Acceleration = LocomotionValues.Acceleration;
}

void URlsAnimInstance::UpdateGroundedMovement(float DeltaTime)
{
	// 更新VelocityBlend
	FVector LocalVelocity = GetLocalVelocity();
	if (LocalVelocity.Normalize())
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
	if (CharacterStates.RotationMode == RlsRotationModeTags::VelocityDirection ||
		CharacterStates.Gait == RlsGaitTags::Sprinting)
	{
		GroundedState.MovementDirection = ERlsMovementDirection::Forward;
	}
	else
	{
		const float AngleThreshold = Settings->Grounded.MovementDirectionThreshold;
		const FRotator Velocity_RotateFromXVector = UKismetMathLibrary::Conv_VectorToRotator(LocomotionBaseValues.Velocity);
		const FRotator ControlRotator = Character->GetControlRotation();
		UKismetMathLibrary::NormalizedDeltaRotator(Velocity_RotateFromXVector, ControlRotator);
		const float DeltaAngle = FMath::UnwindDegrees(Velocity_RotateFromXVector.Yaw - ControlRotator.Yaw);

		if (DeltaAngle < AngleThreshold && DeltaAngle > -AngleThreshold)
		{
			GroundedState.MovementDirection = ERlsMovementDirection::Forward;
		}
		else if (DeltaAngle > AngleThreshold && DeltaAngle < 180.f - AngleThreshold)
		{
			GroundedState.MovementDirection = ERlsMovementDirection::Right;
		}
		else if (DeltaAngle < -AngleThreshold && DeltaAngle > -180.f + AngleThreshold)
		{
			GroundedState.MovementDirection = ERlsMovementDirection::Left;
		}
		else
		{
			GroundedState.MovementDirection = ERlsMovementDirection::Backward;
		}
		UE_LOG(LogTemp, Display, TEXT("DeltaAngle: %hhd"), GroundedState.MovementDirection.bRight);
	}
	
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
		CharacterStates.Gait == RlsGaitTags::Walking ? 0.f : 1.f;

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
}

FVector URlsAnimInstance::GetLocalVelocity() const
{
	return Character->GetActorRotation().UnrotateVector(LocomotionBaseValues.Velocity);
}
