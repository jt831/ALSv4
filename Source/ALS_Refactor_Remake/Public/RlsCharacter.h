#pragma once

#include "CoreMinimal.h"
#include "State/RlsCharacterStates.h"
#include "State/RlsLocomotionValues.h"
#include "GameFramework/Character.h"
#include "RlsCharacter.generated.h"

class URlsAnimInstance;
struct FRlsStandingState;
class URlsCharacterSettings;
class URlsCharacterMovementComponent;

UCLASS(AutoExpandCategories=("Settings|Rls Character", "Settings|Rls Character|Desired State"))
class ALS_REFACTOR_REMAKE_API ARlsCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings|Rls Character")
	TObjectPtr<URlsCharacterSettings> Settings;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Settings|Rls Character")
	TObjectPtr<URlsCharacterMovementComponent> MovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Settings|Rls Character")
	TObjectPtr<URlsAnimInstance> AnimInstance;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Settings|Rls Character", Transient)
	bool bInit{true};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Settings|Rls Character", Transient)
	bool bInitRotation{true};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Settings|Rls Character", Transient)
	FRotator TargetRotation{ForceInit};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Settings|Rls Character", Transient)
	FVector PreviousVelocity{ForceInit};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Settings|Rls Character", Transient)
	FRotator PreviousControlRotation{ForceInit};
	
	// 角色状态
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings|Rls Character", Transient, meta=(Categories="Rls.LocomotionMode"))
	FGameplayTag LocomotionMode{RlsLocomotionModeTags::Grounded};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings|Rls Character", Transient, meta=(Categories="Rls.LocomotionMode"))
	FGameplayTag PreviousLocomotionMode{RlsLocomotionModeTags::Grounded};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Settings|Rls Character", Transient, meta=(Categories="Rls.RotationMode"))
	FGameplayTag DesiredRotationMode{RlsRotationModeTags::VelocityDirection};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings|Rls Character", Transient, meta=(Categories="Rls.RotationMode"))
	FGameplayTag RotationMode{RlsRotationModeTags::ViewDirection};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings|Rls Character", Transient, meta=(Categories="Rls.Stance"))
	FGameplayTag Stance{RlsStanceTags::Standing};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Settings|Rls Character", Transient, meta=(Categories="Rls.Gait"))
	FGameplayTag DesiredGait{RlsGaitTags::Running};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings|Rls Character", Transient, meta=(Categories="Rls.Gait"))
	FGameplayTag Gait{RlsGaitTags::Running};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings|Rls Character", Transient, meta=(Categories="Rls.LocomotionAction"))
	FGameplayTag LocomotionAction{RlsLocomotionActionTags::None};
	
	// 速度加速度这些运动信息
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Settings|Rls Character", Transient)
	FRlsLocomotionValues LocomotionValues;
private:
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	FRotator TargetRotator{ForceInit};
	
public:
	ARlsCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode = 0) override;
	
	// 角色状态
	void SetDesiredGait(const FGameplayTag& NewState);
	const FGameplayTag& GetDesiredGait() const;
	void SetDesiredRotationMode(const FGameplayTag& NewDesiredRotationMode);
	const FGameplayTag& GetDesiredRotationMode() const;
	
	// 给ABP传递角色信息
	FGameplayTag GetRotationMode() const {return RotationMode;}
	FGameplayTag GetGait() const {return Gait;}
	FGameplayTag GetStance() const {return Stance;}
	FGameplayTag GetLocomotionMode() const {return LocomotionMode;}
	FRlsLocomotionValues GetLocomotionValues() const {return LocomotionValues;}

protected:
	virtual void OnJumped_Implementation() override;
	virtual void Jump() override;
	
private:
	void UpdateLocomotionValues(float DeltaTime);

	void UpdateCharacterRotation(float DeltaTime);
	void UpdateGroundedRotation(float DeltaTime);
	
	// 角色状态
	void UpdateCharacterStates();

	void SetLocomotionMode(const FGameplayTag& NewState);
	
	void UpdateRotationMode();
	void SetRotationMode(const FGameplayTag& NewState);
	
	void UpdateGait();
	bool CanSprint();
	void SetGait(const FGameplayTag& NewState);
	
	// 工具
	FVector CalculateAcceleration(float DeltaTime);
	void SetCharacterRotation(const FRotator& Target, float DeltaTime, float ConstInterpSpeed, float InterpSpeed);
	float MapSpeedToRange();
	float CalculateRotationInterpSpeed();
};

