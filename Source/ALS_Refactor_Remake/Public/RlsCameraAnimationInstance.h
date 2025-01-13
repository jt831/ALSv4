// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Utility/RlsGameplayTag.h"
#include "RlsCameraAnimationInstance.generated.h"

class ARlsCharacter;
class URlsCameraComponent;

UCLASS()
class ALS_REFACTOR_REMAKE_API URlsCameraAnimationInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
	TObjectPtr<ARlsCharacter> Character;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
	TObjectPtr<URlsCameraComponent> Camera;

	UPROPERTY(visibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
	FGameplayTag Gait{RlsGaitTags::Walking};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
	FGameplayTag Stance{RlsStanceTags::Standing};

public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaTime) override;
};
