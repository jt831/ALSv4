#pragma once

#include "RlsGroundedState.generated.h"

USTRUCT(BlueprintType)
struct ALS_REFACTOR_REMAKE_API FRlsVelocityBlendState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS")
	uint8 bInitializationRequired : 1 {true};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ClampMax = 1))
	float ForwardAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ClampMax = 1))
	float BackwardAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ClampMax = 1))
	float LeftAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ClampMax = 1))
	float RightAmount{0.0f};
};

USTRUCT(BlueprintType)
struct ALS_REFACTOR_REMAKE_API FRlsRotationYawOffsetsState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = -180, ClampMax = 180, ForceUnits = "deg"))
	float ForwardAngle{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = -180, ClampMax = 180, ForceUnits = "deg"))
	float BackwardAngle{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = -180, ClampMax = 180, ForceUnits = "deg"))
	float LeftAngle{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = -180, ClampMax = 180, ForceUnits = "deg"))
	float RightAngle{0.0f};
};

UENUM(BlueprintType)
enum class ERlsMovementDirection : uint8
{
	Forward,
	Backward,
	Left,
	Right
};

USTRUCT(BlueprintType)
struct ALS_REFACTOR_REMAKE_API FRlsMovementDirection
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS")
	bool bForward {true};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS")
	bool bBackward {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS")
	bool bLeft {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS")
	bool bRight {false};

	constexpr FRlsMovementDirection() = default;

	constexpr FRlsMovementDirection(const ERlsMovementDirection direction)
	{
		bForward = direction == ERlsMovementDirection::Forward;
		bBackward = direction == ERlsMovementDirection::Backward;
		bLeft = direction == ERlsMovementDirection::Left;
		bRight = direction == ERlsMovementDirection::Right;
	}
};

UENUM(BlueprintType)
enum class ERlsHipDirection : uint8
{
	Forward,
	ForwardLeft,
	ForwardRight,
	Backward,
	BackwardLeft,
	BackwardRight
};

USTRUCT()
struct FTransitionInfo
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<UAnimSequenceBase> Sequence;

	UPROPERTY()
	float BlendInTime {0.2f};

	UPROPERTY()
	float BlendOutTime {0.2f};

	UPROPERTY()
	float StartTime {0.f};

	UPROPERTY()
	float PlayRate {1.0f};

	UPROPERTY()
	float StopBlendOutTime {0.2f};
};

USTRUCT(BlueprintType)
struct ALS_REFACTOR_REMAKE_API FRlsGroundedState
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="RLS")
	float FeetCrossCurveAmount{0.f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="RLS")
	float FootPlantedCurveAmount{0.f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS")
	FRlsVelocityBlendState VelocityBlend;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS")
	FRlsMovementDirection MovementDirection;

	// 角色位于八向运动的哪个状态
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS")
	ERlsHipDirection HipDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS")
	FRlsRotationYawOffsetsState RotationYawOffsets;

	// Cpp自用。为播放蒙太奇提供参数
	UPROPERTY()
	FTransitionInfo TransitionInfo;
};
