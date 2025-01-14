// Fill out your copyright notice in the Description page of Project Settings.

#include "RlsCharacter.h"
#include "RlsAnimInstance.h"
#include "RlsLinkedAnimInstance.h"

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
