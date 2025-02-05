#pragma once

#include "Utility/RlsGameplayTag.h"
#include "RlsCharacterStates.generated.h"


USTRUCT(BlueprintType)
struct ALS_REFACTOR_REMAKE_API FRlsDesiredCharacterStates
{
	/*
	 * 在只考虑用户输入与当前角色状态的情况下，角色应该达到的状态
	 */
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Settings|Rls Character", Transient, meta=(Categories="Rls.LocomotionMode"))
	FGameplayTag DesiredLocomotionMode{RlsLocomotionModeTags::Grounded};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Settings|Rls Character", Transient, meta=(Categories="Rls.RotationMode"))
	FGameplayTag DesiredRotationMode{RlsRotationModeTags::VelocityDirection};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Settings|Rls Character", Transient, meta=(Categories="Rls.Stance"))
	FGameplayTag DesiredStance{RlsStanceTags::Standing};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Settings|Rls Character", Transient, meta=(Categories="Rls.Gait"))
	FGameplayTag DesiredGait{RlsGaitTags::Running};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Settings|Rls Character", Transient, meta=(Categories="Rls.LocomotionAction"))
	FGameplayTag DesiredLocomotionAction{RlsLocomotionActionTags::None};
};

USTRUCT(BlueprintType)
struct ALS_REFACTOR_REMAKE_API FRlsCharacterStates
{
	/*
	 * 记录当前角色最终状态
	 */
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings|Rls Character", Transient, meta=(Categories="Rls.LocomotionMode"))
	FGameplayTag LocomotionMode{RlsLocomotionModeTags::Grounded};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings|Rls Character", Transient, meta=(Categories="Rls.RotationMode"))
	FGameplayTag RotationMode{RlsRotationModeTags::ViewDirection};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings|Rls Character", Transient, meta=(Categories="Rls.Stance"))
	FGameplayTag Stance{RlsStanceTags::Standing};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings|Rls Character", Transient, meta=(Categories="Rls.Gait"))
	FGameplayTag Gait{RlsGaitTags::Running};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings|Rls Character", Transient, meta=(Categories="Rls.LocomotionAction"))
	FGameplayTag LocomotionAction{RlsLocomotionActionTags::None};
};
