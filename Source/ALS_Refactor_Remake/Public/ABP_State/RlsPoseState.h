#pragma once

#include "RlsPoseState.generated.h"

USTRUCT(BlueprintType)
struct ALS_REFACTOR_REMAKE_API FRlsPoseState
{
	/*
	 * 动画曲线值
	 */
	GENERATED_BODY()

	// 地面为1，其余为0
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS", Meta = (ClampMin = 0, ClampMax = 1))
	float GroundedAmount{1.0f};

	// 空中为1，其余为0
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS", Meta = (ClampMin = 0, ClampMax = 1))
	float InAirAmount{0.0f};

	// 站立姿态为1，其余为0
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS", Meta = (ClampMin = 0, ClampMax = 1))
	float StandingAmount{1.0f};

	// 蹲伏姿态为1，其余为0
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS", Meta = (ClampMin = 0, ClampMax = 1))
	float CrouchingAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS", Meta = (ClampMin = 0, ClampMax = 1))
	float MovingAmount{0.0f};

	// 走、跑、冲刺为1/2/3
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS", Meta = (ClampMin = 0, ClampMax = 3))
	float GaitAmount{0.0f};
	// 限制范围到01
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS", Meta = (ClampMin = 0, ClampMax = 1))
	float GaitWalkingAmount{0.0f};
	// 减1后限制范围到01
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS", Meta = (ClampMin = 0, ClampMax = 1))
	float GaitRunningAmount{0.0f};
	// 减2后限制范围到01
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS", Meta = (ClampMin = 0, ClampMax = 1))
	float GaitSprintingAmount{0.0f};

	// GaitAmount / GroundedAmount，以达到近似瞬间切换的效果
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS", Meta = (ClampMin = 0, ClampMax = 3))
	float UnweightedGaitAmount{0.0f};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS", Meta = (ClampMin = 0, ClampMax = 1))
	float UnweightedGaitWalkingAmount{0.0f};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS", Meta = (ClampMin = 0, ClampMax = 1))
	float UnweightedGaitRunningAmount{0.0f};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS", Meta = (ClampMin = 0, ClampMax = 1))
	float UnweightedGaitSprintingAmount{0.0f};
};
