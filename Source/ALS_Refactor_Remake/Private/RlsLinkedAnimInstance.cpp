// Fill out your copyright notice in the Description page of Project Settings.

#include "RlsLinkedAnimInstance.h"
#include "RlsCharacter.h"
#include "RlsAnimInstance.h"

URlsLinkedAnimInstance::URlsLinkedAnimInstance()
{
	bUseMainInstanceMontageEvaluationData = true;
}

void URlsLinkedAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Parent = Cast<URlsAnimInstance>(GetSkelMeshComponent()->GetAnimInstance());
	Character = Cast<ARlsCharacter>(GetOwningActor());
}

void URlsLinkedAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void URlsLinkedAnimInstance::SetHipsDirection(ERlsHipDirection HipDirection)
{
	if (IsValid(Parent))
	{
		Parent->SetHipsDirection(HipDirection);
	}
}
