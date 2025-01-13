#include "Utility/RlsGameplayTag.h"

namespace RlsLocomotionModeTags
{
	UE_DEFINE_GAMEPLAY_TAG(Grounded, FName{TEXT("Rls.LocomotionMode.Grounded")})
	UE_DEFINE_GAMEPLAY_TAG(InAir, FName{TEXT("Rls.LocomotionMode.InAir")})
}

namespace RlsRotationModeTags
{
	UE_DEFINE_GAMEPLAY_TAG(VelocityDirection, FName{TEXT("Rls.RotationMode.VelocityDirection")})
	UE_DEFINE_GAMEPLAY_TAG(ViewDirection, FName{TEXT("Rls.RotationMode.ViewDirection")})
}

namespace RlsStanceTags
{
	UE_DEFINE_GAMEPLAY_TAG(Standing, FName{TEXT("Rls.Stance.Standing")})
	UE_DEFINE_GAMEPLAY_TAG(Crouching, FName{TEXT("Rls.Stance.Crouching")})
}

namespace RlsGaitTags
{
	UE_DEFINE_GAMEPLAY_TAG(Walking, FName{TEXT("Rls.Gait.Walking")})
	UE_DEFINE_GAMEPLAY_TAG(Running, FName{TEXT("Rls.Gait.Running")})
	UE_DEFINE_GAMEPLAY_TAG(Sprinting, FName{TEXT("Rls.Gait.Sprinting")})
}

namespace RlsLocomotionActionTags
{
	UE_DEFINE_GAMEPLAY_TAG(Rolling, FName(TEXT("Rls.LocomotionAction.Rolling")))
	UE_DEFINE_GAMEPLAY_TAG(Mantling, FName(TEXT("Rls.LocomotionAction.Mantling")))
}