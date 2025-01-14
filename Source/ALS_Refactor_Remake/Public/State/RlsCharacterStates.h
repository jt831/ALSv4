#pragma once

#include "Utility/RlsGameplayTag.h"
#include "RlsCharacterStates.generated.h"

USTRUCT(BlueprintType)
struct ALS_REFACTOR_REMAKE_API FRlsCharacterStates
{
	/*
	 * 记录角色当前状态
	 */
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Settings|Rls Character", Transient, meta=(Categories="Rls.LocomotionMode"))
	FGameplayTag LocomotionMode{RlsLocomotionModeTags::Grounded};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Settings|Rls Character", Transient, meta=(Categories="Rls.RotationMode"))
	FGameplayTag RotationMode{RlsRotationModeTags::ViewDirection};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Settings|Rls Character", Transient, meta=(Categories="Rls.Stance"))
	FGameplayTag Stance{RlsStanceTags::Standing};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Settings|Rls Character", Transient, meta=(Categories="Rls.Gait"))
	FGameplayTag Gait{RlsGaitTags::Running};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Settings|Rls Character", Transient, meta=(Categories="Rls.LocomotionAction"))
	FGameplayTag LocomotionAction{RlsLocomotionActionTags::None};
};