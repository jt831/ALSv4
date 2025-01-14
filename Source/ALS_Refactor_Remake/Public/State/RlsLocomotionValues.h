#pragma once

#include "RlsLocomotionValues.generated.h"

USTRUCT(BlueprintType)
struct ALS_REFACTOR_REMAKE_API FRlsLocomotionValues
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float Speed2D{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS")
	bool bHasVelocity{false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS")
	FVector Velocity{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS")
	FVector PreviousVelocity{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS")
	FVector Acceleration{ForceInit};
};