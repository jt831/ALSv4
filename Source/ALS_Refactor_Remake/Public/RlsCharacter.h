#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/MovementComponent.h"
#include "RlsCharacter.generated.h"

UCLASS(AutoExpandCategories=("Settings|Rls Character", "Settings|Rls Character|Desired State"))
class ALS_REFACTOR_REMAKE_API ARlsCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings|Rls Character")
	FVector RlsCharacterLocation;
public:
	// Sets default values for this character's properties
	ARlsCharacter();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
