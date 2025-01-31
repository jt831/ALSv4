#pragma once

#include "RlsLocomotionAnimBaseValues.generated.h"

USTRUCT(BlueprintType)
struct ALS_REFACTOR_REMAKE_API FRlsLocomotionAnimBaseValues
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS")
	uint8 bHasInput : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS", Meta = (ClampMin = -180, ClampMax = 180, ForceUnits = "deg"))
	float InputYawAngle{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float Speed{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS")
	FVector Velocity{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS")
	FVector WorldLocation{ForceInit};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS")
	float DeltaDistance{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS")
	float DistanceSpeed{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS", Meta = (ClampMin = -180, ClampMax = 180, ForceUnits = "deg"))
	float VelocityYawAngle{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS")
	FVector Acceleration{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS", Meta = (ClampMin = 0, ForceUnits = "cm/s^2"))
	float MaxAcceleration{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS", Meta = (ClampMin = 0))
	float MaxBrakingDeceleration{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS", Meta = (ClampMin = 0, ClampMax = 1))
	float WalkableFloorAngleCos{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS")
	uint8 bMoving : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS")
	uint8 bHasAcceleration : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS")
	uint8 bMovingSmooth : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS", Meta = (ClampMin = -180, ClampMax = 180, ForceUnits = "deg"))
	float TargetYawAngle{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS")
	FVector Location{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS")
	FRotator Rotation{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS")
	FQuat RotationQuaternion{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS", Meta = (ForceUnits = "deg/s"))
	float YawSpeed{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS", Meta = (ForceUnits = "x"))
	float Scale{1.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS", Meta = (ClampMin = 0, ForceUnits = "cm"))
	float CapsuleRadius{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS", Meta = (ClampMin = 0, ForceUnits = "cm"))
	float CapsuleHalfHeight{0.0f};
};
