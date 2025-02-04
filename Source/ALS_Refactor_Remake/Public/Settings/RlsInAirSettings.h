#pragma once

#include "RlsInAirSettings.generated.h"

USTRUCT(BlueprintType)
struct ALS_REFACTOR_REMAKE_API FRlsInAirSettings
{
	GENERATED_BODY()

	// 根据该值与跳跃时速度的比值来确定动画播放速率
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RLS", meta=(ClampMin=0.f))
	float PlayRateSpeed {600.f};

	// 最大跳跃动画播放速率
	UPROPERTY(editAnywhere, BlueprintReadWrite, Category="RLS", meta=(ClampMin=0.f))
	float MaxPlayRate {1.5f};

	// 最小跳跃动画播放速率
	UPROPERTY(editAnywhere, BlueprintReadWrite, Category="RLS", meta=(ClampMin=0.f))
	float MinPlayRate {1.2f};

	// 落地检测，最大下落速度
	UPROPERTY(editAnywhere, BlueprintReadWrite, Category="RLS", meta=(ClampMin=0.f))
	float MaxVerticalSpeed {4000.f};

	// 落地检测，最小下落速度。当实际下落速度小于该值时，不会开启落地检测
	UPROPERTY(editAnywhere, BlueprintReadWrite, Category="RLS", meta=(ClampMin=0.f))
	float MinVerticalSpeed {200.f};

	// 最大检测距离
	UPROPERTY(editAnywhere, BlueprintReadWrite, Category="RLS", meta=(ClampMin=0.f))
	float MaxSweepDistance {2000.f};

	// 最小检测距离
	UPROPERTY(editAnywhere, BlueprintReadWrite, Category="RLS", meta=(ClampMin=0.f))
	float MinSweepDistance {150.f};

	// 根据距离混合姿势曲线
	UPROPERTY(editAnywhere, BlueprintReadWrite, Category="RLS")
	TObjectPtr<UCurveFloat> GroundPredictionAmountCurve;
};