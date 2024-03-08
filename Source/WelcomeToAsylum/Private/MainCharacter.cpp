// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SpotLightComponent.h"
#include "InteractionComponent.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;

	SpringArm = CreateDefaultSubobject <USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetMesh());
	SpringArm->TargetArmLength = 0.f;

	ViewCamera = CreateDefaultSubobject <UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(SpringArm);
	ViewCamera->bUsePawnControlRotation = true;

	FlashlightSpringArm = CreateDefaultSubobject <USpringArmComponent>(TEXT("FlashlightSpringArm"));
	FlashlightSpringArm->SetupAttachment(ViewCamera);
	FlashlightSpringArm->TargetArmLength = 10.f;
	FlashlightSpringArm->bEnableCameraRotationLag = true;
	FlashlightSpringArm->CameraRotationLagSpeed = 20.f;

	Flashlight = CreateDefaultSubobject <USpotLightComponent>(TEXT("Flashlight"));
	Flashlight->SetupAttachment(FlashlightSpringArm);
	Flashlight->AttenuationRadius = 1200.f;
	Flashlight->bUseIESBrightness = true;

	InteractionComp = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComp"));

}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AMainCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMainCharacter::LookUp);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AMainCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &AMainCharacter::SprintStart);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &AMainCharacter::SprintStop);
	PlayerInputComponent->BindAction(TEXT("FlashlightToggle"), IE_Pressed, this, &AMainCharacter::ToggleFlashlight);

}

void AMainCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.f))
	{
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.f))
	{
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AMainCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AMainCharacter::SprintStart()
{
	GetCharacterMovement()->MaxWalkSpeed = 1000.f;
}

void AMainCharacter::SprintStop()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void AMainCharacter::ToggleFlashlight()
{
	if (bLightState)
	{
		bLightState = false;
		Flashlight->SetVisibility(false, false);
	}
	else
	{
		bLightState = true;
		Flashlight->SetVisibility(true, false);
	}
}

void AMainCharacter::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}

