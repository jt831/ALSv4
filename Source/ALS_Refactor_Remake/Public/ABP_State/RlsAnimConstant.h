#pragma once

#include "Utility/RlsConstants.h"
#include "RlsAnimConstant.generated.h"

USTRUCT(BlueprintType)
struct ALS_REFACTOR_REMAKE_API FRlsAnimConstant
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RLS")
	FName DistanceCurveName{URlsConstants::DistanceCurveName()};
	
};