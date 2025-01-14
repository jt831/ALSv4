#pragma once

#include "CoreMinimal.h"
#include "State/RlsCharacterStates.h"
#include "State/RlsLocomotionValues.h"
#include "GameFramework/Character.h"
#include "RlsCharacter.generated.h"

struct FRlsStandingState;

UCLASS(AutoExpandCategories=("Settings|Rls Character", "Settings|Rls Character|Desired State"))
class ALS_REFACTOR_REMAKE_API ARlsCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	// 角色当前状态。比如是行走还是奔跑？在地面或是空中？
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Settings|Rls Character", Transient)
	FRlsCharacterStates CharacterStates;
	
	// 速度加速度这些运动信息
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Settings|Rls Character", Transient)
	FRlsLocomotionValues LocomotionValues;
	
public:
	ARlsCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 接口
	FRlsCharacterStates GetCharacterStates() const {return CharacterStates;}
	FRlsLocomotionValues GetLocomotionValues() const {return LocomotionValues;}

private:
	virtual void UpdateLocomotionValues(float DeltaTime);

private:
	FVector CalculateAcceleration(float DeltaTime);
};
