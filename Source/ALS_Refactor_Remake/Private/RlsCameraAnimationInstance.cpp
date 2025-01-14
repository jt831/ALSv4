// Fill out your copyright notice in the Description page of Project Settings.


#include "RlsCameraAnimationInstance.h"

#include "RlsCameraComponent.h"
#include "RlsCharacter.h"

void URlsCameraAnimationInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ARlsCharacter>(GetOwningActor());
	Camera = Cast<URlsCameraComponent>(GetSkelMeshComponent());
}

void URlsCameraAnimationInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	
	if (!IsValid(Character) || !IsValid(Camera)) return;

	Gait = Character->GetCharacterStates().Gait;
	Stance = Character->GetCharacterStates().Stance;
}
