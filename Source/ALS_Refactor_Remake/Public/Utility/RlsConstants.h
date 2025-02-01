#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "RlsConstants.generated.h"

UCLASS(meta=(BlueprintThreadSafe))
class ALS_REFACTOR_REMAKE_API URlsConstants : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	// 相机
	UFUNCTION(BlueprintPure, Category="RLS|Constants|Animation Curves", meta = (ReturnDisplayName="Animation Curves"))
	static const FName& RotationLagCurveName();

	UFUNCTION(BlueprintPure, Category="RLS|Constants|Animation Curves", meta = (ReturnDisplayName="Animation Curves"))
	static const FName& PivotLagSpeedXCurveName();

	UFUNCTION(BlueprintPure, Category="RLS|Constants|Animation Curves", meta = (ReturnDisplayName="Animation Curves"))
	static const FName& PivotLagSpeedYCurveName();

	UFUNCTION(BlueprintPure, Category="RLS|Constants|Animation Curves", meta = (ReturnDisplayName="Animation Curves"))
	static const FName& PivotLagSpeedZCurveName();

	UFUNCTION(BlueprintPure, Category="RLS|Constants|Animation Curves", meta = (ReturnDisplayName="Animation Curves"))
	static const FName& PivotOffsetXCurveName();

	UFUNCTION(BlueprintPure, Category="RLS|Constants|Animation Curves", meta = (ReturnDisplayName="Animation Curves"))
	static const FName& PivotOffsetYCurveName();

	UFUNCTION(BlueprintPure, Category="RLS|Constants|Animation Curves", meta = (ReturnDisplayName="Animation Curves"))
	static const FName& PivotOffsetZCurveName();

	UFUNCTION(BlueprintPure, Category="RLS|Constants|Animation Curves", meta = (ReturnDisplayName="Animation Curves"))
	static const FName& CameraOffsetXCurveName();

	UFUNCTION(BlueprintPure, Category="RLS|Constants|Animation Curves", meta = (ReturnDisplayName="Animation Curves"))
	static const FName& CameraOffsetYCurveName();

	UFUNCTION(BlueprintPure, Category="RLS|Constants|Animation Curves", meta = (ReturnDisplayName="Animation Curves"))
	static const FName& CameraOffsetZCurveName();

	UFUNCTION(BlueprintPure, Category="RLS|Constants|Animation Curves", meta = (ReturnDisplayName="Animation Curves"))
	static const FName& DistanceCurveName();

	// 角色
	UFUNCTION(BlueprintPure, Category="RLS|Constants|Sockets", meta = (ReturnDisplayName="Socket Name"))
	static const FName& RootBoneName();
	UFUNCTION(BlueprintPure, Category="RLS|Constants|Sockets", meta = (ReturnDisplayName="Socket Name"))
	static const FName& HeadBoneName();
	UFUNCTION(BlueprintPure, Category="RLS|Constants|Sockets", meta = (ReturnDisplayName="Socket Name"))
	static const FName& LeftFootIkName();
	UFUNCTION(BlueprintPure, Category="RLS|Constants|Sockets", meta = (ReturnDisplayName="Socket Name"))
	static const FName& RightFootIkName();

	UFUNCTION(BlueprintPure, Category="RLS|Constants|Slots")
	static const FName& FootStopSlotName();

	UFUNCTION(BlueprintPure, Category="RLS|Constants|Animation Curves", meta = (ReturnDisplayName="Animation Curves"))
	static const FName& PoseGroundedCurveName();
	UFUNCTION(BlueprintPure, Category="RLS|Constants|Animation Curves", meta = (ReturnDisplayName="Animation Curves"))
	static const FName& PoseInAirCurveName();
	UFUNCTION(BlueprintPure, Category="RLS|Constants|Animation Curves", meta = (ReturnDisplayName="Animation Curves"))
	static const FName& PoseStandingCurveName();
	UFUNCTION(BlueprintPure, Category="RLS|Constants|Animation Curves", meta = (ReturnDisplayName="Animation Curves"))
	static const FName& PoseCrouchingCurveName();
	UFUNCTION(BlueprintPure, Category="RLS|Constants|Animation Curves", meta = (ReturnDisplayName="Animation Curves"))
	static const FName& PoseMovingCurveName();
	UFUNCTION(BlueprintPure, Category="RLS|Constants|Animation Curves", meta = (ReturnDisplayName="Animation Curves"))
	static const FName& PoseGaitCurveName();
	UFUNCTION(BlueprintPure, Category="RLS|Constants|Animation Curves", meta = (ReturnDisplayName="Animation Curves"))
	static const FName& SprintBlockCurveName();
	UFUNCTION(BlueprintPure, Category="RLS|Constants|Animation Curves", meta = (ReturnDisplayName="Animation Curves"))
	static const FName& FeetCrossingCurveName();
	UFUNCTION(BlueprintPure, Category="RLS|Constants|Animation Curves", meta = (ReturnDisplayName="Animation Curves"))
	static const FName& FootPlantedCurveName();
	UFUNCTION(BlueprintPure, Category = "RLS|Constants|Animation Curves", Meta = (ReturnDisplayName = "Animation Curves"))
	static const FName& RotationYawOffsetCurveName();
	UFUNCTION(BlueprintPure, Category = "RLS|Constants|Animation Curves", Meta = (ReturnDisplayName = "Animation Curves"))
	static const FName& FootLeftIkCurveName();
	UFUNCTION(BlueprintPure, Category = "RLS|Constants|Animation Curves", Meta = (ReturnDisplayName = "Animation Curves"))
	static const FName& FootRightIkCurveName();
	UFUNCTION(BlueprintPure, Category = "RLS|Constants|Animation Curves", Meta = (ReturnDisplayName = "Animation Curves"))
	static const FName& FootLeftLockCurveName();
	UFUNCTION(BlueprintPure, Category = "RLS|Constants|Animation Curves", Meta = (ReturnDisplayName = "Animation Curves"))
	static const FName& FootRightLockCurveName();
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

inline const FName& URlsConstants::DistanceCurveName()
{
	static const FName Name{TEXT("Distance")};
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

inline const FName& URlsConstants::LeftFootIkName()
{
	static const FName Name{TEXT("ik_foot_l")};
	return Name;
}

inline const FName& URlsConstants::RightFootIkName()
{
	static const FName Name{TEXT("ik_foot_r")};
	return Name;
}

inline const FName& URlsConstants::FootStopSlotName()
{
	static const FName Name{TEXT("FootStop")};
	return Name;
}


inline const FName& URlsConstants::PoseGaitCurveName()
{
	/*
	 * 同原版Weight_Gait。步行为1，奔跑为2，冲刺为3
	 */
	static const FName Name{TEXT("PoseGait")};
	return Name;
}
inline const FName& URlsConstants::PoseGroundedCurveName()
{
	/*
	 * 地面为1，其余为0
	 */
	static const FName Name{TEXT("PoseGrounded")};
	return Name;
}

inline const FName& URlsConstants::PoseInAirCurveName()
{
	static const FName Name{TEXTVIEW("PoseInAir")};
	return Name;
}

inline const FName& URlsConstants::PoseStandingCurveName()
{
	static const FName Name{TEXTVIEW("PoseStanding")};
	return Name;
}

inline const FName& URlsConstants::PoseCrouchingCurveName()
{
	static const FName Name{TEXTVIEW("PoseCrouching")};
	return Name;
}

inline const FName& URlsConstants::PoseMovingCurveName()
{
	static const FName Name{TEXTVIEW("PoseMoving")};
	return Name;
}

inline const FName& URlsConstants::SprintBlockCurveName()
{
	static const FName Name{TEXTVIEW("SprintBlock")};
	return Name;
}

inline const FName& URlsConstants::FeetCrossingCurveName()
{
	static const FName Name{TEXTVIEW("FeetCrossing")};
	return Name;
}

inline const FName& URlsConstants::FootPlantedCurveName()
{
	static const FName Name{TEXTVIEW("FootPlanted")};
	return Name;
}

inline const FName& URlsConstants::RotationYawOffsetCurveName()
{
	static const FName Name{TEXTVIEW("RotationYawOffset")};
	return Name;
}

inline const FName& URlsConstants::FootLeftIkCurveName()
{
	static const FName Name{TEXTVIEW("FootLeftIk")};
	return Name;
}

inline const FName& URlsConstants::FootRightIkCurveName()
{
	static const FName Name{TEXTVIEW("FootRightIk")};
	return Name;
}

inline const FName& URlsConstants::FootLeftLockCurveName()
{
	static const FName Name{TEXTVIEW("FootLeftIk")};
	return Name;
}

inline const FName& URlsConstants::FootRightLockCurveName()
{
	static const FName Name{TEXTVIEW("FootRightIk")};
	return Name;
}