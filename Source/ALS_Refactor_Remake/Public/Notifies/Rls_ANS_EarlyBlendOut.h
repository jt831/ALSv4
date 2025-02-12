#pragma once

#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Rls_ANS_EarlyBlendOut.generated.h"

UCLASS(DisplayName="Rls EarlyBlendOut ANS")
class ALS_REFACTOR_REMAKE_API URls_ANS_EarlyBlendOut : public UAnimNotifyState
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings", Meta=(ForceUnits="s"))
	float BlendOutDuration {0.25f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	bool bCheckInput {true};
	
public:
	URls_ANS_EarlyBlendOut();

	virtual FString GetNotifyName_Implementation() const override;

#if WITH_EDITOR
	virtual bool CanBePlaced(UAnimSequenceBase* Animation) const override;
#endif

	virtual void BranchingPointNotifyTick(FBranchingPointNotifyPayload& BranchingPointPayload, float FrameDeltaTime) override;
};

