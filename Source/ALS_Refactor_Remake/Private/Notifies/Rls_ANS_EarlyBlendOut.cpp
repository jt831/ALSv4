#include "Notifies/Rls_ANS_EarlyBlendOut.h"

#include "RlsCharacter.h"

URls_ANS_EarlyBlendOut::URls_ANS_EarlyBlendOut()
{
	bIsNativeBranchingPoint = true;
}

FString URls_ANS_EarlyBlendOut::GetNotifyName_Implementation() const
{
	return FString("ANS_EarlyBlendOut");
}

bool URls_ANS_EarlyBlendOut::CanBePlaced(UAnimSequenceBase* Animation) const
{
	return IsValid(Animation) && Animation->IsA<UAnimMontage>();
}

void URls_ANS_EarlyBlendOut::BranchingPointNotifyTick(FBranchingPointNotifyPayload& NotifyPayload,
	float FrameDeltaTime)
{
	Super::BranchingPointNotifyTick(NotifyPayload, FrameDeltaTime);

	const auto* Mesh = NotifyPayload.SkelMeshComponent;
	auto* AnimInstance = IsValid(Mesh) ? Mesh->GetAnimInstance() : nullptr;
	const auto* Character = IsValid(Mesh) ? Cast<ARlsCharacter>(Mesh->GetOwner()) : nullptr;

	if (IsValid(Character) && IsValid(AnimInstance) && 
		(bCheckInput && Character->GetLocomotionValues().bHasInput))
	{
		auto* MontageInstance = AnimInstance->GetMontageInstanceForID(NotifyPayload.MontageInstanceID);
		if (MontageInstance != nullptr)
		{
			const auto* Montage = MontageInstance->Montage.Get();

			FMontageBlendSettings BlendOutSettings {Montage->BlendOut};
			BlendOutSettings.BlendMode = Montage->BlendModeOut;
			BlendOutSettings.BlendProfile = Montage->BlendProfileOut;
			BlendOutSettings.Blend.BlendTime = BlendOutDuration;
			
			MontageInstance->Stop(BlendOutSettings);
		}
	}
}


