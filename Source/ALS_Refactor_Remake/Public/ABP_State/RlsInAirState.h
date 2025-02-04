#pragma once

#include "RlsInAirState.generated.h"

USTRUCT(BlueprintType)
struct ALS_REFACTOR_REMAKE_API FRLSInAirState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RLS")
	uint8 bJumped :1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RLS")
	uint8 bDesiredJumped :1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RLS", meta=(ClampMin=0.f))
	float JumpPlayRate{1.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS", Meta = (ClampMin = 0, ClampMax = 1))
	float GroundPredictionAmount{1.0f};
};