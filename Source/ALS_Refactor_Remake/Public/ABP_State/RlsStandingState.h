#pragma once

#include "RlsStandingState.generated.h"

USTRUCT(BlueprintType)
struct ALS_REFACTOR_REMAKE_API FRlsStandingState
{
	/*
	 * 给ABP用的二级参数
	 */
	GENERATED_BODY()

	// Locomotion 走跑混合三件套
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLS", meta = (ClampMin = 0, ClampMax = 1))
	float StrideBlendAmount{0.};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rls", meta = (ClampMin = 0, ClampMax = 1))
	float WalkRunBlendAmount{0.};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rls", meta = (ClampMin = 0, ClampMax = 3))
	float PlayRate{1.};
	
	// 控制冲刺落地时腿部IK的扭曲幅度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rls", meta = (ClampMin = 0, ClampMax = 1))
	float SprintBlockAmount{0.};
	
};
