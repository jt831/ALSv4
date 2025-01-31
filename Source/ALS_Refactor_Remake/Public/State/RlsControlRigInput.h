#pragma once

#include "Units/RigUnit.h"
#include "RlsControlRigInput.generated.h"

USTRUCT(BlueprintType)
struct ALS_REFACTOR_REMAKE_API FRlsControlRigInput
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RLS")
	bool bEnableLeftFootIK {true};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RLS")
	bool bEnableRightFootIK {true};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RLS")
	FRigElementKey PelvisItem;
	
};