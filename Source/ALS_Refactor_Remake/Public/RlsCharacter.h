#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "GameFramework/Character.h"
#include "Utility/RlsGameplayTag.h"
#include "RlsCharacter.generated.h"


UCLASS(AutoExpandCategories=("Settings|Rls Character", "Settings|Rls Character|Desired State"))
class ALS_REFACTOR_REMAKE_API ARlsCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Settings|Rls Character", Transient, meta=(Categories="Rls.LocomotionMode"))
	FGameplayTag LocomotionMode{RlsLocomotionModeTags::Grounded};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Settings|Rls Character", Transient, meta=(Categories="Rls.RotationMode"))
	FGameplayTag RotationMode{RlsRotationModeTags::ViewDirection};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Settings|Rls Character", Transient, meta=(Categories="Rls.Stance"))
	FGameplayTag Stance{RlsStanceTags::Standing};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Settings|Rls Character", Transient, meta=(Categories="Rls.Gait"))
	FGameplayTag Gait{RlsGaitTags::Running};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Settings|Rls Character", Transient, meta=(Categories="Rls.LocomotionAction"))
	FGameplayTag LocomotionAction;
	
public:
	// Sets default values for this character's properties
	ARlsCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 获得GamePlayTag
	FGameplayTag GetLocomotionMode() const { return LocomotionMode; }
	FGameplayTag GetRotationMode() const { return RotationMode; }
	FGameplayTag GetStance() const { return Stance; }
	FGameplayTag GetGait() const { return Gait; }
	FGameplayTag GetLocomotionAction() const { return LocomotionAction; }

private:
	virtual void UpdateCharacterInfo();
};
