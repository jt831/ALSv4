#pragma once

#include "Curves/CurveVector.h"
#include "Settings/RlsStandingSettings.h"
#include "Settings/RlsCrouchingSettings.h"
#include "RlsGroundedSettings.generated.h"

USTRUCT(BlueprintType)
struct ALS_REFACTOR_REMAKE_API FRlsGroundedSettings
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS", meta=(ClampMin=0.f))
	float VelocityBlendInterpSpeed{12.0};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS", meta=(ClampMin=0.f, ClampMax=90.f))
	float MovementDirectionThreshold{70.};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS")
	TObjectPtr<UCurveFloat> RotationYawOffset_FB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS")
	TObjectPtr<UCurveFloat> RotationYawOffset_L;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS")
	TObjectPtr<UCurveFloat> RotationYawOffset_R;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS")
	FRlsStandingSettings Standing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS")
	FRlsCrouchingSettings Crouching;
};