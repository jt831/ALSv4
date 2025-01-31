// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABP_State/RlsGroundedState.h"
#include "Animation/AnimInstance.h"
#include "RlsLinkedAnimInstance.generated.h"

class URlsAnimInstance;
class ARlsCharacter;

UCLASS()
class ALS_REFACTOR_REMAKE_API URlsLinkedAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "State", Transient)
	TObjectPtr<URlsAnimInstance> Parent;

	UPROPERTY(VisibleAnywhere, Category = "State", Transient)
	TObjectPtr<ARlsCharacter> Character;
	
public:
	URlsLinkedAnimInstance();

	virtual void NativeInitializeAnimation() override;

	virtual void NativeBeginPlay() override;

protected:
	UFUNCTION(BlueprintPure, Category = "RLS|Linked Animation Instance",
		Meta = (BlueprintThreadSafe, ReturnDisplayName = "Parent"))
	URlsAnimInstance* GetParent() const;

	UFUNCTION(BlueprintCallable, Category = "RLS|Linked Animation Instance", Meta = (BlueprintThreadSafe))
	void SetHipsDirection(ERlsHipDirection HipDirection);
};

inline URlsAnimInstance* URlsLinkedAnimInstance::GetParent() const
{
	return Parent.Get();
}
