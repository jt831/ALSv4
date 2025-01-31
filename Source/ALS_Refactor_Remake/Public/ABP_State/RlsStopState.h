#pragma once

#include "RlsStopState.generated.h"

USTRUCT(BlueprintType)
struct ALS_REFACTOR_REMAKE_API FRlsStopState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rls", Transient)
	TObjectPtr<UAnimSequence> WalkToStop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rls", Transient)
	TObjectPtr<UAnimSequence> RunToStop;
};