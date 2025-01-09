// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/Character.h"
#include "RlsCameraComponent.h"

URlsCameraComponent::URlsCameraComponent()
{
}

void URlsCameraComponent::OnRegister()
{
	Character = Cast<ACharacter>(GetOwner());
	Super::OnRegister();
}

void URlsCameraComponent::BeginPlay()
{
	Super::BeginPlay();
}

void URlsCameraComponent::ApplyCameraInfo(struct FMinimalViewInfo& OutResult)
{
	FVector Location = Character->GetActorLocation();
	OutResult.Location = FVector(Location.X - 200, Location.Y, Location.Z + 100);
	OutResult.Rotation = Character->GetViewRotation();
	OutResult.FOV = 90;
}


