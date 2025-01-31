#pragma once

#include "RlsStartState.generated.h"

USTRUCT(BlueprintType)
struct ALS_REFACTOR_REMAKE_API FRlsStartState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rls", Transient)
	TObjectPtr<UAnimSequence> WalkToStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rls", Transient)
	TObjectPtr<UAnimSequence> RunToStart;
};