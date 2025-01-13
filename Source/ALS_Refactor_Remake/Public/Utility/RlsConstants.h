#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "RlsConstants.generated.h"

UCLASS(meta=(BlueprintThreadSafe))
class ALS_REFACTOR_REMAKE_API URlsConstants : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	// 相机
	UFUNCTION(BlueprintPure, Category="Rls|Constants|Animation Curves", meta = (ReturnDisplayName="Animation Curves"))
	static const FName& RotationLagCurveName();

	UFUNCTION(BlueprintPure, Category="Rls|Constants|Animation Curves", meta = (ReturnDisplayName="Animation Curves"))
	static const FName& PivotLagSpeedXCurveName();

	UFUNCTION(BlueprintPure, Category="Rls|Constants|Animation Curves", meta = (ReturnDisplayName="Animation Curves"))
	static const FName& PivotLagSpeedYCurveName();

	UFUNCTION(BlueprintPure, Category="Rls|Constants|Animation Curves", meta = (ReturnDisplayName="Animation Curves"))
	static const FName& PivotLagSpeedZCurveName();

	UFUNCTION(BlueprintPure, Category="Rls|Constants|Animation Curves", meta = (ReturnDisplayName="Animation Curves"))
	static const FName& PivotOffsetXCurveName();

	UFUNCTION(BlueprintPure, Category="Rls|Constants|Animation Curves", meta = (ReturnDisplayName="Animation Curves"))
	static const FName& PivotOffsetYCurveName();

	UFUNCTION(BlueprintPure, Category="Rls|Constants|Animation Curves", meta = (ReturnDisplayName="Animation Curves"))
	static const FName& PivotOffsetZCurveName();

	UFUNCTION(BlueprintPure, Category="Rls|Constants|Animation Curves", meta = (ReturnDisplayName="Animation Curves"))
	static const FName& CameraOffsetXCurveName();

	UFUNCTION(BlueprintPure, Category="Rls|Constants|Animation Curves", meta = (ReturnDisplayName="Animation Curves"))
	static const FName& CameraOffsetYCurveName();

	UFUNCTION(BlueprintPure, Category="Rls|Constants|Animation Curves", meta = (ReturnDisplayName="Animation Curves"))
	static const FName& CameraOffsetZCurveName();

	// 角色
	UFUNCTION(BlueprintPure, Category="Rls|Constants|Sockets", meta = (ReturnDisplayName="Socket Name"))
	static const FName& RootBoneName();

	UFUNCTION(BlueprintPure, Category="Rls|Constants|Sockets", meta = (ReturnDisplayName="Socket Name"))
	static const FName& HeadBoneName();
};

inline const FName& URlsConstants::RotationLagCurveName()
{
	static const FName Name{TEXT("RotationLag")};
	return Name;
}

inline const FName& URlsConstants::PivotLagSpeedXCurveName()
{
	static const FName Name{TEXT("LocationLagX")};
	return Name;
}

inline const FName& URlsConstants::PivotLagSpeedYCurveName()
{
	static const FName Name{TEXT("LocationLagY")};
	return Name;
}

inline const FName& URlsConstants::PivotLagSpeedZCurveName()
{
	static const FName Name{TEXT("LocationLagZ")};
	return Name;
}

inline const FName& URlsConstants::PivotOffsetXCurveName()
{
	static const FName Name{TEXT("PivotOffsetX")};
	return Name;
}

inline const FName& URlsConstants::PivotOffsetYCurveName()
{
	static const FName Name{TEXT("PivotOffsetY")};
	return Name;
}

inline const FName& URlsConstants::PivotOffsetZCurveName()
{
	static const FName Name{TEXT("PivotOffsetZ")};
	return Name;
}

inline const FName& URlsConstants::CameraOffsetXCurveName()
{
	static const FName Name{TEXT("CameraOffsetX")};
	return Name;
}

inline const FName& URlsConstants::CameraOffsetYCurveName()
{
	static const FName Name{TEXT("CameraOffsetY")};
	return Name;
}

inline const FName& URlsConstants::CameraOffsetZCurveName()
{
	static const FName Name{TEXT("CameraOffsetZ")};
	return Name;
}

inline const FName& URlsConstants::RootBoneName()
{
	static const FName Name{TEXT("root")};
	return Name;
}

inline const FName& URlsConstants::HeadBoneName()
{
	static const FName Name{TEXT("head")};
	return Name;
}