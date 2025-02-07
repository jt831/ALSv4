// Fill out your copyright notice in the Description page of Project Settings.

#include "RlsCharacter.h"

#include "RlsAnimInstance.h"
#include "RlsCharacterMovementComponent.h"
#include "RlsCharacterSettings.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Utility/RlsConstants.h"

// Sets default values
ARlsCharacter::ARlsCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MovementComponent = Cast<URlsCharacterMovementComponent>(GetCharacterMovement());

}

// Called every frame
void ARlsCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateCharacterStates();
	UpdateLocomotionValues(DeltaTime);
	UpdateCharacterRotation(DeltaTime);
	bInit = false;
}

void ARlsCharacter::PostInitializeComponents()
{
	AnimInstance = Cast<URlsAnimInstance>(GetMesh()->GetAnimInstance());
	
	Super::PostInitializeComponents();
}

void ARlsCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);
	PreviousLocomotionMode = LocomotionMode;
	switch (GetCharacterMovement()->MovementMode)
	{
		case MOVE_Walking:
		case MOVE_NavWalking:
			SetLocomotionMode(RlsLocomotionModeTags::Grounded);
			break;

		case MOVE_Falling:
			SetLocomotionMode(RlsLocomotionModeTags::InAir);
			break;

		default:
			SetLocomotionMode(FGameplayTag::EmptyTag);
			break;
	}
}

void ARlsCharacter::SetDesiredGait(const FGameplayTag& NewState)
{
	if (DesiredGait == NewState) return;
	DesiredGait = NewState;
}

const FGameplayTag& ARlsCharacter::GetDesiredGait() const
{
	return DesiredGait;
}

void ARlsCharacter::OnJumped_Implementation()
{
	Super::OnJumped_Implementation();

	if (IsValid(AnimInstance))
	{
		AnimInstance->Jump();
	}
}

void ARlsCharacter::Jump()
{
	if (LocomotionMode == RlsLocomotionModeTags::Grounded &&
		Stance == RlsStanceTags::Standing &&
		LocomotionAction == RlsLocomotionActionTags::None)
	{
		Super::Jump();
	}
}

void ARlsCharacter::UpdateLocomotionValues(float DeltaTime)
{
	LocomotionValues.Velocity = GetVelocity();

	LocomotionValues.bHasVelocity = LocomotionValues.Velocity.Length() > 0.;

	LocomotionValues.bHasInput = MovementComponent->GetCurrentAcceleration().Length() > UE_SMALL_NUMBER;

	LocomotionValues.Speed2D = FVector(LocomotionValues.Velocity.X, LocomotionValues.Velocity.Y, 0).Length();

	LocomotionValues.Acceleration = CalculateAcceleration(DeltaTime);
	LocomotionValues.bHasAcceleration = !FMath::IsNearlyZero(MovementComponent->GetCurrentAcceleration().Length());

	LocomotionValues.ControlRotation = GetViewRotation();

	if (bInit)
	{
		PreviousVelocity = LocomotionValues.Velocity;
		PreviousControlRotation = LocomotionValues.ControlRotation;
	}
	LocomotionValues.ControlRotationRate = LocomotionValues.ControlRotation - PreviousControlRotation;

	InputMoveLR = 0.;
	InputMoveUD = 0.;

	PreviousStartClimbDelayTime = StartClimbDelayTime;
	StartClimbDelayTime = StartClimbDelayTime <= 0. ? 0. : StartClimbDelayTime - DeltaTime;
}

void ARlsCharacter::UpdateCharacterRotation(float DeltaTime)
{
	if (LocomotionMode == RlsLocomotionModeTags::Grounded)
	{
		UpdateGroundedRotation(DeltaTime);
	}
}

void ARlsCharacter::UpdateGroundedRotation(float DeltaTime)
{
	if (LocomotionAction == RlsLocomotionActionTags::None &&
		(LocomotionValues.bHasVelocity || HasAnyRootMotion()))
	{
		/*const FRotator VelocityRotator = FMath::IsNearlyZero(LocomotionValues.Velocity.Length()) ?
			UKismetMathLibrary::Conv_VectorToRotator(MovementComponent->GetCurrentAcceleration()):
			UKismetMathLibrary::Conv_VectorToRotator(LocomotionValues.Velocity);*/
		const FRotator VelocityRotator = UKismetMathLibrary::Conv_VectorToRotator(LocomotionValues.Velocity);
		
		const FRotator ViewRotator = GetViewRotation();
		
		if (bInitRotation)
		{
			SetActorRotation(ViewRotator);
			TargetRotation = ViewRotator;
			bInitRotation = false;
			return;
		}
		
		float ConstInterpSpeed = Settings->Grounded.InterpSpeed.CharacterRotationConstInterpSpeed;
		float InterpSpeed = CalculateRotationInterpSpeed();
		
		if (RotationMode == RlsRotationModeTags::VelocityDirection)
		{
			InterpSpeed = Settings->Grounded.InterpSpeed.VelocityDirectionCharacterRotationInterpSpeed;
			ConstTargetRotation = VelocityRotator;
		}
		else
		{
			ConstTargetRotation = ViewRotator;
			
			// 冲刺模式下不需要考虑其他因素
			// 否则需要在斜四方向运动时添加旋转偏移量
			if (Gait != RlsGaitTags::Sprinting)
			{
				if (IsValid(AnimInstance))
				{
					ConstTargetRotation.Yaw += AnimInstance->GetCurveValue(URlsConstants::RotationYawOffsetCurveName());
				}
			}
		}

		ConstTargetRotation.Roll = ConstTargetRotation.Pitch = 0.f;
		SetCharacterRotation(ConstTargetRotation, DeltaTime, ConstInterpSpeed, InterpSpeed);
	}
}

void ARlsCharacter::SetDesiredRotationMode(const FGameplayTag& NewDesiredRotationMode)
{
	if (DesiredRotationMode == NewDesiredRotationMode) return;
	DesiredRotationMode = NewDesiredRotationMode;
}

const FGameplayTag& ARlsCharacter::GetDesiredRotationMode() const
{
	return DesiredRotationMode;
}

void ARlsCharacter::UpdateCharacterStates()
{
	UpdateGait();
	UpdateRotationMode();
	MovementComponent->SetLocomotionMode(LocomotionMode);
}

void ARlsCharacter::SetLocomotionMode(const FGameplayTag& NewState)
{
	if (LocomotionMode == NewState) return;
	LocomotionMode = NewState;
}

void ARlsCharacter::UpdateRotationMode()
{
	// 当角色冲刺时，强制切换为速度方向
	if (Gait == RlsGaitTags::Sprinting)
	{
		SetRotationMode(RlsRotationModeTags::VelocityDirection);
	}
	// 否则自由切换旋转模式
	else
	{
		SetRotationMode(DesiredRotationMode);
	}
}

void ARlsCharacter::SetRotationMode(const FGameplayTag& NewState)
{
	if (RotationMode == NewState) return;
	RotationMode = NewState;
}

void ARlsCharacter::UpdateGait()
{
	// 考虑其他状态
	if (LocomotionAction != RlsLocomotionActionTags::None ||
		LocomotionMode != RlsLocomotionModeTags::Grounded) return;

	// 考虑用户输入与控制器夹角
	FGameplayTag Gait_Part1 = RlsGaitTags::Running;
	if (DesiredGait != RlsGaitTags::Sprinting)
	{
		Gait_Part1 = DesiredGait;
	}
	else if (CanSprint()) Gait_Part1 = RlsGaitTags::Sprinting;

	MovementComponent->SetGait_Part1(Gait_Part1);

	// 考虑当前速度与设置速度的大小关系
	FGameplayTag Gait_Part2;
	if (LocomotionValues.Speed2D < Settings->Grounded.MaxWalkSpeed + 1.f)
	{
		Gait_Part2 = RlsGaitTags::Walking;
	}
	else if (LocomotionValues.Speed2D < Settings->Grounded.MaxRunSpeed || Gait_Part1 != RlsGaitTags::Sprinting)
	{
		Gait_Part2 = RlsGaitTags::Running;
	}
	else
	{
		Gait_Part2 = RlsGaitTags::Sprinting;
	}

	SetGait(Gait_Part2);
}

bool ARlsCharacter::CanSprint()
{
	if (!LocomotionValues.bHasVelocity) return false;
	if (RotationMode == RlsRotationModeTags::VelocityDirection) return true;

	const FRotator Acceleration_RotateFromXVector = UKismetMathLibrary::Conv_VectorToRotator(LocomotionValues.Acceleration);
	const FRotator ControlRotator = GetControlRotation();
	const float DeltaAngle_AC = FMath::UnwindDegrees(Acceleration_RotateFromXVector.Yaw - ControlRotator.Yaw);
	const float AngleThreshold = IsValid(Settings) ? Settings->Grounded.Threshold.AllowSprintAngleThreshold : 50.f;
	
	return FMath::Abs(DeltaAngle_AC) < AngleThreshold;
}

void ARlsCharacter::SetGait(const FGameplayTag& NewState)
{
	if (Gait == NewState) return;
	Gait = NewState;
}

// -------------------------------------------------------------------------------------

FVector ARlsCharacter::CalculateAcceleration(float DeltaTime)
{
	return (LocomotionValues.Velocity - PreviousVelocity) / DeltaTime;
}

void ARlsCharacter::SetCharacterRotation(const FRotator& Target, float DeltaTime, float ConstInterpSpeed,
	float InterpSpeed)
{
	FRotator CharacterRotation = GetActorRotation();
	TargetRotation = FMath::RInterpConstantTo(TargetRotation, Target, DeltaTime, ConstInterpSpeed);
	CharacterRotation = FMath::RInterpTo(CharacterRotation, TargetRotation, DeltaTime, InterpSpeed);

	SetActorRotation(CharacterRotation);
}

float ARlsCharacter::MapSpeedToRange()
{
	/*
	 * 将速度映射为0到3
	 */
	if (!IsValid(Settings)) return 0.;
	
	const float Speed = LocomotionValues.Speed2D;
	const float MaxWalkSpeed = Settings->Grounded.MaxWalkSpeed;
	const float MaxRunSpeed = Settings->Grounded.MaxRunSpeed;
	const float SprintSpeed = Settings->Grounded.SprintSpeed;

	float MappedSpeed = 0.f;
	if (Speed < MaxWalkSpeed)
	{
		MappedSpeed = FMath::GetMappedRangeValueClamped(FFloatRange(0, MaxWalkSpeed),
			FFloatRange(0, 1), Speed);
	}
	else if (Speed < MaxRunSpeed)
	{
		MappedSpeed = FMath::GetMappedRangeValueClamped(FFloatRange(MaxWalkSpeed, MaxRunSpeed),
			FFloatRange(1, 2), Speed);
	}
	else
	{
		MappedSpeed = FMath::GetMappedRangeValueClamped(FFloatRange(MaxRunSpeed, SprintSpeed),
			FFloatRange(2, 3), Speed);
	}

	return MappedSpeed;
}

float ARlsCharacter::CalculateRotationInterpSpeed()
{
	/*
	 * 考虑角色运动速度与控制器旋转速度得出的角色旋转插值速度
	 */
	if (!IsValid(Settings->Grounded.InterpSpeed.ViewDirectionCharacterRotationInterpSpeedCurve)) return 0.f;
	const float MappedSpeed = MapSpeedToRange();
	const float InterpSpeed =
		Settings->Grounded.InterpSpeed.ViewDirectionCharacterRotationInterpSpeedCurve->GetFloatValue(MappedSpeed);
	const float ControlRotationRateYaw = LocomotionValues.ControlRotationRate.Yaw;
	const float MappedAngle = FMath::GetMappedRangeValueClamped(FFloatRange(0, 360),
		FFloatRange(1, 3), ControlRotationRateYaw);

	return InterpSpeed * MappedAngle;
}




