// Fill out your copyright notice in the Description page of Project Settings.

#include "RlsCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ARlsCharacter::ARlsCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->MaxWalkSpeed = 375;
}

// Called every frame
void ARlsCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	UpdateLocomotionValues(DeltaTime);
}

// Called to bind functionality to input
void ARlsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

// 每帧更新角色数值
void ARlsCharacter::UpdateLocomotionValues(float DeltaTime)
{
	LocomotionValues.Velocity = GetVelocity();

	LocomotionValues.bHasVelocity = LocomotionValues.Velocity.Length() > 0.;

	LocomotionValues.Speed2D = FVector(LocomotionValues.Velocity.X, LocomotionValues.Velocity.Y, 0).Length();

	LocomotionValues.Acceleration = CalculateAcceleration(DeltaTime);
}

// -------------------------------------------------------------------------------------

FVector ARlsCharacter::CalculateAcceleration(float DeltaTime)
{
	return (LocomotionValues.Velocity - LocomotionValues.PreviousVelocity) / DeltaTime;
}




