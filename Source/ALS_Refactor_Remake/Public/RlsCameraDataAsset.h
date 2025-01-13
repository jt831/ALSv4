#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Utility/RlsConstants.h"
#include "RlsCameraDataAsset.generated.h"

USTRUCT(BlueprintType)
struct ALS_REFACTOR_REMAKE_API FRlsThirdPersonCameraSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rls|Camera|Settings", Meta=(ClampMin=5, ClampMax=170, ForceUnits="deg"))
	float FOV{90.0f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rls|Camera|Settings")
	FName FirstPivotSocketName = URlsConstants::RootBoneName();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rls|Camera|Settings")
	FName SecondPivotSocketName = URlsConstants::HeadBoneName();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rls|Camera|Settings|Trace", Meta=(ClampMin=5, ClampMax=170, ForceUnits="deg"))
	float TraceRadius{10.0f};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rls|Camera|Settings|Trace", Meta=(ClampMin=5, ClampMax=170, ForceUnits="deg"))
	TEnumAsByte<ECollisionChannel> TraceChannel{ECC_Visibility};
};
UCLASS(Blueprintable, BlueprintType)
class ALS_REFACTOR_REMAKE_API URlsCameraDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Rls|Camera|Settings")
	bool bIgnoreTimeDilation{false};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Rls|Camera|Settings")
	FRlsThirdPersonCameraSettings ThirdPerson;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Rls|Camera|Settings")
	FPostProcessSettings PostProcess;
};
