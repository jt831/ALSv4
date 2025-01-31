// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RlsCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Utility/RlsGameplayTag.h"
#include "RlsCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup="RLS")
class ALS_REFACTOR_REMAKE_API URlsCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="State")
	TObjectPtr<ARlsCharacter> Character;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	FGameplayTag Gait_Part1;

public:
	void SetGait_Part1(const FGameplayTag& NewState);

protected:
	virtual void MoveSmooth(const FVector& InVelocity, const float DeltaSeconds, FStepDownResult* OutStepDownResult = 0) override;
	virtual void PhysWalking(float deltaTime, int32 Iterations) override;
	virtual void PhysNavWalking(float deltaTime, int32 Iterations) override;
	
private:
	URlsCharacterMovementComponent();
	void UpdateGroundedMovement();
};
