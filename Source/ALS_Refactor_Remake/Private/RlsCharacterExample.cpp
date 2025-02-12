#include "RlsCharacterExample.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "RlsCameraComponent.h"
#include "Engine/LocalPlayer.h"
#include "Utility/RlsVector.h"


ARlsCharacterExample::ARlsCharacterExample()
{
	// 创建相机组件
	Camera = CreateDefaultSubobject<URlsCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetMesh());
	Camera->SetRelativeRotation(FRotator(0, 90, 0));

	// 初始化一些参数
	bUseControllerRotationYaw = false;
}

void ARlsCharacterExample::CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult)
{
	if (Camera->IsActive())
	{
		Camera->UpdateCamera(OutResult);
		return;
	}
	Super::CalcCamera(DeltaTime, OutResult);
}

void ARlsCharacterExample::SetupPlayerInputComponent(UInputComponent* Input)
{
	Super::SetupPlayerInputComponent(Input);

	UEnhancedInputComponent* EnhancedInput{Cast<UEnhancedInputComponent>(Input)};

	if (IsValid(EnhancedInput))
	{
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this
			, &ThisClass::Input_OnLook);
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Canceled, this
			, &ThisClass::Input_OnLook);
		EnhancedInput->BindAction(LookMouseAction, ETriggerEvent::Triggered, this
			, &ThisClass::Input_OnLookMouse);
		EnhancedInput->BindAction(LookMouseAction, ETriggerEvent::Canceled, this
			, &ThisClass::Input_OnLookMouse);
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this
			, &ThisClass::Input_OnMove);
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Canceled, this
			, &ThisClass::Input_OnMove);
		EnhancedInput->BindAction(SprintAction, ETriggerEvent::Triggered, this
			, &ThisClass::Input_OnSprint);
		EnhancedInput->BindAction(SprintAction, ETriggerEvent::Canceled, this
			, &ThisClass::Input_OnSprint);
		EnhancedInput->BindAction(WalkAction, ETriggerEvent::Started, this
			, &ThisClass::Input_OnWalk);
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Triggered, this
			, &ThisClass::Input_OnJump);
		EnhancedInput->BindAction(RollAction, ETriggerEvent::Triggered, this
			, &ThisClass::Input_OnRoll);
		EnhancedInput->BindAction(ChangeRotationModeAction, ETriggerEvent::Started, this,
			&ThisClass::Input_OnChangeRotationMode);
	}
}

void ARlsCharacterExample::Input_OnLook(const FInputActionValue& ActionValue)
{
	const FVector2f Value{ActionValue.Get<FVector2D>()};

	AddControllerPitchInput(Value.Y * LookUpRate / 90.);
	AddControllerYawInput(Value.X * LookRightRate / 90.);
}

void ARlsCharacterExample::Input_OnLookMouse(const FInputActionValue& ActionValue)
{
	const FVector2f Value{ActionValue.Get<FVector2D>()};

	AddControllerPitchInput(Value.Y * LookUpMouseRate);
	AddControllerYawInput(Value.X * LookRightMouseRate);
}

void ARlsCharacterExample::Input_OnMove(const FInputActionValue& ActionValue)
{
	const FVector2D Value{URlsVector::ClampMagnitude012D(ActionValue.Get<FVector2D>())};

	InputMoveLR = Value.X;
	InputMoveUD = Value.Y;
	
	const FRotator& ViewRotation = Super::GetViewRotation().GetNormalized();
	const FVector& ViewForwardDir = URlsVector::AngleToDirectionXY(ViewRotation.Yaw);
	const FVector& ViewRightDir = URlsVector::PerpendicularCounterClockwiseXY(ViewForwardDir);

	const FVector& ActorUpVector = GetActorUpVector();
	const FVector& ActorRightVector = GetActorRightVector();

	if (LocomotionMode == RlsLocomotionModeTags::Grounded)
	{
		WorldDirection = ViewForwardDir*Value.Y+ViewRightDir*Value.X;
		AddMovementInput(WorldDirection);
	}
	else if (LocomotionMode == RlsLocomotionModeTags::Climb)
	{
		AddMovementInput(ActorUpVector*Value.Y+ActorRightVector*Value.X);
	}
}

void ARlsCharacterExample::Input_OnWalk(const FInputActionValue& Value)
{
	if (GetDesiredGait() == RlsGaitTags::Walking)
	{
		SetDesiredGait(RlsGaitTags::Running);
	}
	else
	{
		SetDesiredGait(RlsGaitTags::Walking);
	}
}

void ARlsCharacterExample::Input_OnSprint(const FInputActionValue& Value)
{
	SetDesiredGait(Value.Get<bool>() ? RlsGaitTags::Sprinting : RlsGaitTags::Running);
}

void ARlsCharacterExample::Input_OnJump(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		Jump();
	}
}

void ARlsCharacterExample::Input_OnRoll(const FInputActionValue& Value)
{
}

void ARlsCharacterExample::Input_OnFly(const FInputActionValue& Value)
{
}

void ARlsCharacterExample::Input_OnChangeRotationMode(const FInputActionValue& Value)
{
	
	SetDesiredRotationMode(GetDesiredRotationMode()== RlsRotationModeTags::VelocityDirection ?
							RlsRotationModeTags::ViewDirection :
							RlsRotationModeTags::VelocityDirection);
}
