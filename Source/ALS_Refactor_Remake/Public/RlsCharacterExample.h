#pragma once

#include "RlsCharacter.h"
#include "RlsCharacterExample.generated.h"

struct FInputActionValue;
class URlsCameraComponent;
class UInputAction;

UCLASS(AutoExpandCategories=("Settings|RLS InputAction", "Settings|RLS Rate"))
class ALS_REFACTOR_REMAKE_API ARlsCharacterExample : public ARlsCharacter
{
	GENERATED_BODY()
	// 属性
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="RLS")
	TObjectPtr<URlsCameraComponent> Camera;
	
	// 将鼠标的2D空间映射到摄像机旋转值
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings|RLS InputAction",
		meta=(DisplayThumbnail=false))
	TObjectPtr<UInputAction> LookMouseAction;
	
	// 将控制器的旋转值映射到摄像机旋转值
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings|RLS InputAction",
		meta=(DisplayThumbnail=false))
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings|RLS InputAction",
		meta=(DisplayThumbnail=false))
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings|RLS InputAction",
		meta=(DisplayThumbnail=false))
	TObjectPtr<UInputAction> WalkAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings|RLS InputAction",
		meta=(DisplayThumbnail=false))
	TObjectPtr<UInputAction> SprintAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings|RLS InputAction",
		Meta=(DisplayThumbnail=false))
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings|RLS InputAction",
		meta=(DisplayThumbnail=false))
	TObjectPtr<UInputAction> RollAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings|RLS InputAction",
		meta=(DisplayThumbnail=false))
	TObjectPtr<UInputAction> ChangeRotationModeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings|RLS Rate",
		meta=(ClampMin=0, ForceUnits = "x"))
	float LookUpMouseRate=1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings|RLS Rate",
		meta=(ClampMin=0, ForceUnits = "x"))
	float LookRightMouseRate=1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings|RLS Rate",
		meta=(ClampMin=0, ForceUnits = "deg/s"))
	float LookUpRate=90.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings|RLS Rate",
		meta=(ClampMin=0, ForceUnits = "deg/s"))
	float LookRightRate=130.0f;

	// 方法
public:
	ARlsCharacterExample();

protected:
	virtual void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;
	
	virtual void SetupPlayerInputComponent(UInputComponent* Input) override;

private:
	virtual void Input_OnLook(const FInputActionValue& Value);
	
	virtual void Input_OnLookMouse(const FInputActionValue& Value);

	virtual void Input_OnMove(const FInputActionValue& Value);
	
	virtual void Input_OnWalk(const FInputActionValue& Value);

	virtual void Input_OnSprint(const FInputActionValue& Value);

	virtual void Input_OnJump(const FInputActionValue& Value);

	virtual void Input_OnRoll(const FInputActionValue& Value);

	virtual void Input_OnFly(const FInputActionValue& Value);

	virtual void Input_OnChangeRotationMode(const FInputActionValue& Value);
};
