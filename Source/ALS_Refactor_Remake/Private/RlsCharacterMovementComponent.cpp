// Fill out your copyright notice in the Description page of Project Settings.


#include "RlsCharacterMovementComponent.h"

#include "RlsCharacterSettings.h"

URlsCharacterMovementComponent::URlsCharacterMovementComponent()
{
	Character = Cast<ARlsCharacter>(GetOwner());
}

void URlsCharacterMovementComponent::SetGait_Part1(const FGameplayTag& NewState)
{
	if (NewState != Gait_Part1)
	{
		Gait_Part1 = NewState;
	}
}

void URlsCharacterMovementComponent::SetLocomotionMode(const FGameplayTag& NewState)
{
	if (NewState != LocomotionMode)
	{
		LocomotionMode = NewState;
	}
}

void URlsCharacterMovementComponent::PhysWalking(float deltaTime, int32 Iterations)
{
	UpdateGroundedMovement();
	Super::PhysWalking(deltaTime, Iterations);
}

void URlsCharacterMovementComponent::PhysFlying(float deltaTime, int32 Iterations)
{
	UpdateClimbMovement();
	Super::PhysFlying(deltaTime, Iterations);
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

void URlsCharacterMovementComponent::UpdateClimbMovement()
{
	if (!IsValid(Character) || !IsValid(Character->Settings)
		|| LocomotionMode != RlsLocomotionModeTags::Climb) return;

	MaxFlySpeed = Character->Settings->Climb.MaxClimbSpeed;
}
