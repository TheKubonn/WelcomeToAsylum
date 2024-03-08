// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USpotLightComponent;
class UInteractionComponent;

UCLASS()
class WELCOMETOASYLUM_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	// Axis Mappings
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	// Action Mappings
	void SprintStart();
	void SprintStop();
	void ToggleFlashlight();
	void PrimaryInteract();

private:	
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr <USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr <USpringArmComponent> FlashlightSpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr <UCameraComponent> ViewCamera;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr <USpotLightComponent> Flashlight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr <UInteractionComponent> InteractionComp;

	bool bLightState = true;

};
