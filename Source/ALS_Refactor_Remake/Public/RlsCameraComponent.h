// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "RlsCameraComponent.generated.h"

UCLASS(ClassGroup="RLS", Meta = (BlueprintSpawnableComponent),
HideCategories = ("ComponentTick", "Clothing", "Physics", "MasterPoseComponent", "Collision", "AnimationRig",
	"Lighting", "Deformer", "Rendering", "PathTracing", "HLOD", "Navigation", "VirtualTexture", "SkeletalMesh",
	"LeaderPoseComponent", "Optimization", "LOD", "MaterialParameters", "TextureStreaming", "Mobile", "RayTracing"))
class ALS_REFACTOR_REMAKE_API URlsCameraComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State", Transient)
	TObjectPtr<ACharacter> Character;
public:
	URlsCameraComponent();

	virtual void OnRegister() override;

	virtual void BeginPlay() override;

	// 传入计算完成的所有相机信息
	void ApplyCameraInfo(struct FMinimalViewInfo& OutResult);
};
