// Fill out your copyright notice in the Description page of Project Settings.


#include "RlsCharacterMovementComponent.h"

#include "RlsCharacterSettings.h"

void URlsCharacterMovementComponent::SetGait_Part1(const FGameplayTag& NewState)
{
	if (NewState != Gait_Part1)
	{
		Gait_Part1 = NewState;
	}
}

void URlsCharacterMovementComponent::MoveSmooth(const FVector& InVelocity, const float DeltaSeconds,
	FStepDownResult* OutStepDownResult)
{
	if (IsMovingOnGround())
	{
		UpdateGroundedMovement();
	}
	Super::MoveSmooth(InVelocity, DeltaSeconds, OutStepDownResult);
	
}

void URlsCharacterMovementComponent::PhysWalking(float deltaTime, int32 Iterations)
{
	UpdateGroundedMovement();
	Super::PhysWalking(deltaTime, Iterations);
}

void URlsCharacterMovementComponent::PhysNavWalking(const float DeltaTime, const int32 IterationsCount)
{
	UpdateGroundedMovement();

	Super::PhysNavWalking(DeltaTime, IterationsCount);
}

URlsCharacterMovementComponent::URlsCharacterMovementComponent()
{
	Character = Cast<ARlsCharacter>(GetOwner());
}

void URlsCharacterMovementComponent::UpdateGroundedMovement()
{
	if (!IsValid(Character) || !IsValid(Character->Settings)) return;
	
	if (Gait_Part1 == RlsGaitTags::Walking)
	{
		MaxWalkSpeed = Character->Settings->Grounded.MaxWalkSpeed;
	}
	else if (Gait_Part1 == RlsGaitTags::Running)
	{
		MaxWalkSpeed = Character->Settings->Grounded.MaxRunSpeed;
	}
	else if (Gait_Part1 == RlsGaitTags::Sprinting)
	{
		MaxWalkSpeed = Character->Settings->Grounded.SprintSpeed;
	}
	else
	{
		MaxWalkSpeed = Character->Settings->Grounded.MaxRunSpeed;
	}
}
