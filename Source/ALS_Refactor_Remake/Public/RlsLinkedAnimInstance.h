// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	TWeakObjectPtr<URlsAnimInstance> Parent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
	TObjectPtr<ARlsCharacter> Character;
	
public:
	URlsLinkedAnimInstance();

	virtual void NativeInitializeAnimation() override;

	virtual void NativeBeginPlay() override;

protected:
	UFUNCTION(BlueprintPure, Category = "RLS|Linked Animation Instance",
		Meta = (BlueprintThreadSafe, ReturnDisplayName = "Parent"))
	URlsAnimInstance* GetParent() const;
};

inline URlsAnimInstance* URlsLinkedAnimInstance::GetParent() const
{
	return Parent.Get();
}
