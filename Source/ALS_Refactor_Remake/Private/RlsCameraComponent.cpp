// Fill out your copyright notice in the Description page of Project Settings.

#include "RlsCameraComponent.h"

#include "MaterialHLSLTree.h"
#include "GameFramework/Character.h"
#include "RlsCameraDataAsset.h"
#include "Kismet/BlueprintTypeConversions.h"
#include "Utility/RlsConstants.h"

URlsCameraComponent::URlsCameraComponent()
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.TickGroup = TG_PostPhysics;

	bTickInEditor = false;
	bHiddenInGame = true;
}

void URlsCameraComponent::PostLoad()
{
	Super::PostLoad();
	VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

void URlsCameraComponent::OnRegister()
{
	Character = Cast<ACharacter>(GetOwner());
	Mesh = IsValid(Character) ? Character->GetMesh() : nullptr;
	Super::OnRegister();
}

void URlsCameraComponent::RegisterComponentTickFunctions(bool bRegister)
{
	Super::RegisterComponentTickFunctions(bRegister);
	// 让组件Tick在Owner后执行
	AddTickPrerequisiteActor(GetOwner());
}

void URlsCameraComponent::Activate(bool bReset)
{
	// 先初始化一次参数。比如让CameraRotation=Character->GetViewRotation(), CameraLocation = PivotLocation
	if (bReset || ShouldActivate())
	{
		TickCamera(0.0f, false);
	}
	Super::Activate(bReset);
}

void URlsCameraComponent::InitAnim(bool bForceReinit)
{
	Super::InitAnim(bForceReinit);
	AnimationInstance = GetAnimInstance();
}

void URlsCameraComponent::BeginPlay()
{
	ensure(IsValid(GetAnimInstance()));
	ensure(IsValid(Settings));
	ensure(IsValid(Character));
	Super::BeginPlay();
}

void URlsCameraComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	// 是否对相机应用时间膨胀
	if (IsValid(Settings) && !Settings->bIgnoreTimeDilation)
	{
		const float TimeDilation = PreviousGlobalTimeDilation * GetOwner()->CustomTimeDilation;
		DeltaTime = TimeDilation > UE_SMALL_NUMBER ? DeltaTime * TimeDilation : GetWorld()->DeltaRealTimeSeconds;
	}
	PreviousGlobalTimeDilation = GetWorld()->GetWorldSettings()->GetEffectiveTimeDilation();
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (!IsRunningParallelEvaluation())
	{
		TickCamera(DeltaTime);
	}
}

void URlsCameraComponent::CompleteParallelAnimationEvaluation(bool bDoPostAnimationEvaluation)
{
	Super::CompleteParallelAnimationEvaluation(bDoPostAnimationEvaluation);
	// 让当前计算在ABP计算结束后执行
	// 实测下来大部分都在调用这里的Tick
	TickCamera(AnimationInstance->GetDeltaSeconds());
}


void URlsCameraComponent::UpdateCamera(struct FMinimalViewInfo& OutResult)
{
	OutResult.Location = CameraLocation;
	OutResult.Rotation = CameraRotation;
	OutResult.FOV = CameraFOV;

	OutResult.PostProcessBlendWeight = IsValid(Settings) ? 1 : 0;
	if (OutResult.PostProcessBlendWeight > UE_SMALL_NUMBER)
	{
		OutResult.PostProcessSettings = Settings->PostProcess;
	}
}

void URlsCameraComponent::TickCamera(const float DeltaTime, bool bAllowLag)
{
	if (!AnimationInstance || !Settings || !Character) return;
	// 更新相机旋转
	UpdateCameraRotation(CameraRotation, DeltaTime, bAllowLag);
	// 更新相机位移
	UpdateCameraLocation(CameraTargetLocation, CameraLocation, DeltaTime, bAllowLag);
	CameraFOV = IsValid(Settings) ? Settings->ThirdPerson.FOV : 90.f;
}

void URlsCameraComponent::UpdateCameraRotation(FRotator& OutCameraRotation, float DeltaTime, bool bAllowLag)
{
	if (!IsValid(Character) || !IsValid(AnimationInstance)) return;
	const FRotator& CameraTargetRotation = Character->GetViewRotation();
	// 未应用曲线
	if (!bAllowLag)
	{
		OutCameraRotation = CameraTargetRotation;
		return;
	}
	
	const float RotationLag = AnimationInstance->GetCurveValue(URlsConstants::RotationLagCurveName());
	OutCameraRotation = FMath::RInterpTo(OutCameraRotation, CameraTargetRotation, DeltaTime, RotationLag);
}

void URlsCameraComponent::UpdateCameraLocation(FVector& OutCameraTargetLocation, FVector& OutCameraLocation, float DeltaTime, bool bAllowLag)
{
	// 获得相机基础位置
	AppendThirdPersonCameraPivotLocation(OutCameraTargetLocation, DeltaTime, bAllowLag);
	// 添加偏移
	FVector PivotLocation = OutCameraTargetLocation + GetPivotOffset();
	// 绕点旋转
	FVector CameraFinalLocation = PivotLocation + GetCameraOffset();
	// 碰撞检测
	AppendSphereTrace(CameraFinalLocation);
	
	OutCameraLocation = CameraFinalLocation;
}

void URlsCameraComponent::AppendThirdPersonCameraPivotLocation(FVector& OutCameraLocation, float DeltaTime, bool bAllowLag)
{
	if (!IsValid(Mesh)) return;

	// 获得目标位置，基本上位于Pivot处
	// 至于为什么不直接用Pivot bone的位置，估计是为了减轻抖动
	FVector FirstPivotLocation = Mesh->GetSocketLocation(Settings->ThirdPerson.FirstPivotSocketName);
	FVector SecondPivotLocation = Mesh->GetSocketLocation(Settings->ThirdPerson.SecondPivotSocketName);
	FVector PivotLocation = (FirstPivotLocation + SecondPivotLocation) * 0.5f;

	if (!IsValid(AnimationInstance) || !bAllowLag)
	{
		OutCameraLocation = PivotLocation;
		return;
	}

	// 插值
	float PivotLagSpeed_X = AnimationInstance->GetCurveValue(URlsConstants::PivotLagSpeedXCurveName());
	float PivotLagSpeed_Y = AnimationInstance->GetCurveValue(URlsConstants::PivotLagSpeedYCurveName());
	float PivotLagSpeed_Z = AnimationInstance->GetCurveValue(URlsConstants::PivotLagSpeedZCurveName());
	
	OutCameraLocation.X = FMath::FInterpTo(OutCameraLocation.X, PivotLocation.X, DeltaTime, PivotLagSpeed_X);
	OutCameraLocation.Y = FMath::FInterpTo(OutCameraLocation.Y, PivotLocation.Y, DeltaTime, PivotLagSpeed_Y);
	OutCameraLocation.Z = FMath::FInterpTo(OutCameraLocation.Z, PivotLocation.Z, DeltaTime, PivotLagSpeed_Z);
}

FVector URlsCameraComponent::GetPivotOffset()
{
	FVector PivotOffset = FVector::ZeroVector;
	
	if (!IsValid(Character)) return PivotOffset;
	
	FRotator PivotRotation = Character->GetActorRotation();
	float PivotOffset_X = AnimationInstance->GetCurveValue(URlsConstants::PivotOffsetXCurveName());
	float PivotOffset_Y = AnimationInstance->GetCurveValue(URlsConstants::PivotOffsetYCurveName());
	float PivotOffset_Z = AnimationInstance->GetCurveValue(URlsConstants::PivotOffsetZCurveName());
	PivotOffset = PivotRotation.RotateVector(FVector(PivotOffset_X, PivotOffset_Y, PivotOffset_Z));
	
	return PivotOffset;
}

FVector URlsCameraComponent::GetCameraOffset()
{
	if (!IsValid(Character)) return FVector::ZeroVector;
	
	float CameraOffset_X = AnimationInstance->GetCurveValue(URlsConstants::CameraOffsetXCurveName());
	float CameraOffset_Y = AnimationInstance->GetCurveValue(URlsConstants::CameraOffsetYCurveName());
	float CameraOffset_Z = AnimationInstance->GetCurveValue(URlsConstants::CameraOffsetZCurveName());
	FVector CameraOffset = CameraRotation.RotateVector(FVector(CameraOffset_X, CameraOffset_Y, CameraOffset_Z));

	return CameraOffset;
}

void URlsCameraComponent::AppendSphereTrace(FVector& OutCameraLocation)
{
	if (!IsValid(Mesh)) return;

	// 应用球体追踪
	FVector StartLocation = Mesh->GetSocketLocation(Settings->ThirdPerson.SecondPivotSocketName);
	FVector EndLocation = OutCameraLocation;
	const float MeshScale = Mesh->GetComponentScale().Z;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(Settings->ThirdPerson.TraceRadius * MeshScale);
	TEnumAsByte<ECollisionChannel> TranceChannel = Settings->ThirdPerson.TraceChannel;
	static const FName MainTraceTag{FString::Printf(TEXT("%hs (Main Trace)"), __FUNCTION__)};
	FHitResult Hit;

	GetWorld()->SweepSingleByChannel(Hit, StartLocation, EndLocation, FQuat::Identity, TranceChannel, Sphere, {MainTraceTag, false, GetOwner()});
	if (Hit.bBlockingHit && !Hit.bStartPenetrating)
	{
		OutCameraLocation = Hit.Location;
	}
}
