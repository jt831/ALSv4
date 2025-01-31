// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "RlsCameraComponent.generated.h"

class URlsCameraDataAsset;
UCLASS(ClassGroup="RLS", Meta = (BlueprintSpawnableComponent),
HideCategories = ("ComponentTick", "Clothing", "Physics", "MasterPoseComponent", "Collision", "AnimationRig",
	"Lighting", "Deformer", "Rendering", "PathTracing", "HLOD", "Navigation", "VirtualTexture", "SkeletalMesh",
	"LeaderPoseComponent", "Optimization", "LOD", "MaterialParameters", "TextureStreaming", "Mobile", "RayTracing"))
class ALS_REFACTOR_REMAKE_API URlsCameraComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Camera")
	TObjectPtr<URlsCameraDataAsset> Settings;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera|Debug", Transient)
	TObjectPtr<ACharacter> Character;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera|Debug", Transient)
	TObjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera|Debug", Transient)
	TObjectPtr<UAnimInstance> AnimationInstance;
	
	// ForceInit:初始化为0
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera|Debug", Transient)
	FVector CameraLocation{ForceInit};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera|Debug", Transient)
	FVector CameraTargetLocation{ForceInit};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera|Debug", Transient)
	FRotator CameraRotation{ForceInit};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera|Debug", Transient)
	float CameraFOV{ForceInit};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera|Debug", Transient)
	float PreviousGlobalTimeDilation{1.0f};


public:
	URlsCameraComponent();

	virtual void PostLoad() override;
	
	virtual void OnRegister() override;

	virtual void RegisterComponentTickFunctions(bool bRegister) override;

	virtual void Activate(bool bReset = false) override;

	virtual void InitAnim(bool bForceReinit) override;
	
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void CompleteParallelAnimationEvaluation(bool bDoPostAnimationEvaluation) override;

	// 传入计算完成的所有相机信息
	void UpdateCamera(struct FMinimalViewInfo& OutResult);
	
private:
	void TickCamera(float DeltaTime, bool bAllowLag=true);

	void UpdateCameraRotation(FRotator& CameraRotation, float DeltaTime, bool bAllowLag);

	void UpdateCameraLocation(FVector& CameraTargetLocation, FVector& CameraLocation, float DeltaTime, bool bAllowLag);
	void AppendThirdPersonCameraPivotLocation(FVector& CameraTargetLocation, float DeltaTime, bool bAllowLag);
	FVector GetPivotOffset();
	FVector GetCameraOffset();
	void AppendSphereTrace(FVector& CameraTargetLocation);
};
