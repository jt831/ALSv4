// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RlsCharacterSettings.generated.h"

USTRUCT(BlueprintType)
struct ALS_REFACTOR_REMAKE_API FRlsCharacterSettingsGroundedInterpSpeed
{
	GENERATED_BODY()
	
	// 角色旋转值的普遍插值速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rls", meta = (ClampMin = 0, ClampMax = 1000))
	float CharacterRotationConstInterpSpeed{500.f};
	
	// 在RotationMode为VelocityDirection时，角色旋转值与速度方向的插值速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rls", meta = (ClampMin = 0, ClampMax = 90))
	float VelocityDirectionCharacterRotationInterpSpeed{30.f};

	// 在RotationMode为ViewDirection时，角色旋转值与控制器方向的插值速度曲线
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rls")
	TObjectPtr<UCurveFloat> ViewDirectionCharacterRotationInterpSpeedCurve;
};

USTRUCT(BlueprintType)
struct ALS_REFACTOR_REMAKE_API FRlsCharacterSettingsGroundedThreshold
{
	GENERATED_BODY()

	// 允许冲刺的加速度与控制器方向的最大夹角
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rls", meta = (ClampMin = 0, ClampMax = 90))
	float AllowSprintAngleThreshold{50.f};
	
};

USTRUCT(BlueprintType)
struct ALS_REFACTOR_REMAKE_API FRlsCharacterSettingsGrounded
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rls", meta = (ClampMin = 0, ForceUnits="cm/s"))
	float MaxWalkSpeed{175.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rls", meta = (ClampMin = 0, ForceUnits="cm/s"))
	float MaxRunSpeed{375.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rls", meta = (ClampMin = 0, ForceUnits="cm/s"))
	float SprintSpeed{650.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rls")
	FRlsCharacterSettingsGroundedThreshold Threshold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rls")
	FRlsCharacterSettingsGroundedInterpSpeed InterpSpeed;
};

USTRUCT(BlueprintType)
struct ALS_REFACTOR_REMAKE_API FRlsCharacterSettingsClimb
{
	GENERATED_BODY()

	// 最小可攀爬物体的宽度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rls", meta = (ClampMin = 0, ForceUnits="cm"))
	float MinClimbedWidth {30.f};

	// 最小可攀爬物体的高度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rls", meta = (ClampMin = 0, ForceUnits="cm"))
	float MinClimbedHeight {160.f};

	// 最大攀爬速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rls", meta = (ClampMin = 0, ForceUnits="cm/s"))
	float MaxClimbSpeed{100.f};
};

UCLASS(BlueprintType)
class ALS_REFACTOR_REMAKE_API URlsCharacterSettings : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rls")
	FRlsCharacterSettingsGrounded Grounded;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rls")
	FRlsCharacterSettingsClimb Climb;
};
