// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RlsAnimInstanceSettings.h"
#include "ABP_State/RlsPoseState.h"
#include "ABP_State/RlsGroundedState.h"
#include "ABP_State/RlsInAirState.h"
#include "ABP_State/RlsStandingState.h"
#include "ABP_State/RlsAnimConstant.h"
#include "ABP_State/RlsLocomotionAnimBaseValues.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "State/RlsCharacterStates.h"
#include "State/RlsControlRigInput.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State")
	FRlsControlRigInput ControlRigInput;

	//  ------------------------- 用于表示角色当前状态 --------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State", Transient)
	uint8 bIsFirstUpdate: 1 {true};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State", Transient)
	FGameplayTag LocomotionMode{RlsLocomotionModeTags::Grounded};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State", Transient)
	FGameplayTag RotationMode{RlsRotationModeTags::ViewDirection};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State", Transient)
	FGameplayTag Stance{RlsStanceTags::Standing};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State", Transient)
	FGameplayTag Gait{RlsGaitTags::Running};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State", Transient)
	FGameplayTag LocomotionAction{RlsLocomotionActionTags::None};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State", Transient)
	FRlsLocomotionAnimBaseValues LocomotionBaseValues;

	// 动画曲线值，一般用于插值。比如在走跑冲刺三种状态下的值分别为123的GaitAmount
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State", Transient)
	FRlsPoseState PoseState;
	// -------------------------- 直接用于ABP中更改动画 -----------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
	FRlsGroundedState GroundedState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
	FRLSInAirState InAirState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient)
	FRlsStandingState StandingState;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	FRlsAnimConstant ConstantValue;
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
	virtual void NativePostEvaluateAnimation() override;
	
	UFUNCTION(BlueprintCallable, Category = "RLS|Animation Instance", meta = (BlueprintThreadSafe))
	void PlayTransition(UAnimSequenceBase* Sequence, float BlendInTime=0.2, float BlendOutTime=0.2, float StartTime=0., float PlayRate=1.);

	UFUNCTION(BlueprintCallable, Category="RLS|Animation Instance", meta = (BlueprintThreadSafe))
	void StopTransition(float BlendOutDuration = 0.2);
	
	UFUNCTION(BlueprintCallable, Category = "RLS|Animation Instance", meta = (BlueprintThreadSafe))
	void SetHipsDirection(ERlsHipDirection HipDirection);

public:
	UFUNCTION(BlueprintCallable, Category = "RLS|Animation Instance", meta = (BlueprintThreadSafe))
	void UpdateInAir();

	void UpdateGroundPrediction();
	
protected:
	UFUNCTION(BlueprintCallable, Category="RLS|Animation Instance", Meta=(BlueprintThreadSafe, ReturnDisplayName="CharacterMovementComponent"))
	UCharacterMovementComponent* GetCharacterMovementComponent() const;

public:
	void Jump();
	
private:
	void UpdateInfoFromCharacter();
	void UpdateGroundedMovement(float DeltaTime);
	void UpdateInAirOnGameThread();
	void UpdateStandingMovement();
	void UpdatePoseState();
	void UpdateBaseValues(float DeltaTime);
	void PlayQueuedTransition();
	void StopQueuedTransition();
	void UpdateControlRigInput();
	void UpdateFootLockInfo(float& Alpha, FVector& Location, FRotator& Rotation, const FName& FootLockCurve, const FName& FootIkBone);
	FVector GetLocalVelocity() const;
};

inline void URlsAnimInstance::Jump()
{
	// 跳跃时，在角色蓝图中调用
	InAirState.bDesiredJumped = true;
}

