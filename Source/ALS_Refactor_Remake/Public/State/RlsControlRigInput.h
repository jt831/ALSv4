#pragma once

#include "Units/RigUnit.h"
#include "RlsControlRigInput.generated.h"

USTRUCT(BlueprintType)
struct ALS_REFACTOR_REMAKE_API FRlsFootLockInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RLS")
	float LeftFootLockWeight{0.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RLS")
	float RightFootLockWeight{0.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RLS")
	FVector LeftFootLocation {ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RLS")
	FVector RightFootLocation {ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RLS")
	FRotator LeftFootRotation {ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RLS")
	FRotator RightFootRotation {ForceInit};
};
USTRUCT(BlueprintType)
struct ALS_REFACTOR_REMAKE_API FRlsControlRigInput
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RLS")
	float LeftFootIKWeight {1.};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RLS")
	float RightFootIKWeight {1.};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RLS")
	FRlsFootLockInfo FootLockInfo;
	
};