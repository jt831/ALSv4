#pragma once

#include "RlsStandingSettings.generated.h"

USTRUCT(BlueprintType)
struct ALS_REFACTOR_REMAKE_API FRlsStandingSettings
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float AnimatedWalkSpeed{150.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float AnimatedRunSpeed{350.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float AnimatedSprintSpeed{600.0f};

	// 将实际速度映射到步长
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS")
	TObjectPtr<UCurveFloat> StrideBlendAmountWalkCurve;
	
	// 将实际速度映射到步长
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS")
	TObjectPtr<UCurveFloat> StrideBlendAmountRunCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float PivotActivationSpeedThreshold{200.0f};
};