// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RlsAnimInstanceSettings.h"
#include "ABP_State/RlsPoseState.h"
#include "ABP_State/RlsGroundedState.h"
#include "ABP_State/RlsStandingState.h"
#include "ABP_State/RlsLocomotionAnimBaseValues.h"
#include "State/RlsCharacterStates.h"
#include "RlsAnimInstance.generated.h"

class ARlsCharacter;

UCLASS()
class ALS_REFACTOR_REMAKE_API URlsAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings")
	TObjectPtr<URlsAnimInstanceSettings> Settings;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State", Transient)
	TObjectPtr<ARlsCharacter> Character;

	//  ------------------------- 用于表示角色当前状态 --------------------------
	// 直接从BP接收过来的参数与状态
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State", Transient)
	FRlsCharacterStates CharacterStates;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State", Transient)
	FRlsLocomotionAnimBaseValues LocomotionBaseValues;

	// 动画曲线值，一般用于插值。比如在走跑冲刺三种状态下的值分别为123的GaitAmount
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State", Transient)
	FRlsPoseState PoseState;
	// -------------------------- 直接用于ABP中更改动画 -----------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
	FRlsGroundedState GroundedState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
	FRlsStandingState StandingState;
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	
private:
	void UpdateInfoFromCharacter();
	void UpdateGroundedMovement(float DeltaTime);
	void UpdateStandingMovement();
	void UpdatePoseState();
	FVector GetLocalVelocity() const;
};
