// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Settings/RlsGroundedSettings.h"
#include "Engine/DataAsset.h"
#include "RlsAnimInstanceSettings.generated.h"

UCLASS(Blueprintable, BlueprintType)
class ALS_REFACTOR_REMAKE_API URlsAnimInstanceSettings : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	FRlsGroundedSettings Grounded;
};
