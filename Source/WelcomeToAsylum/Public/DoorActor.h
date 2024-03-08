// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "GameplayInterface.h"
#include "DoorActor.generated.h"

class UStaticMeshComponent;
class UCurveFloat;

UCLASS()
class WELCOMETOASYLUM_API ADoorActor : public AActor, public IGameplayInterface
{
	GENERATED_BODY()
	
public:	
	ADoorActor();
	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	virtual void BeginPlay() override;

	FTimeline Timeline;

	UPROPERTY(EditAnywhere)
	UCurveFloat* CurveFloat;

	UPROPERTY(EditAnywhere)
	bool bIsDoorClosed = true;

	UPROPERTY(EditAnywhere)
	float DoorRotateAngle = 90.f;

	UFUNCTION()
	void OpenDoor(float Value);

private:

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TObjectPtr <UStaticMeshComponent> DoorFrame;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TObjectPtr <UStaticMeshComponent> Door;
	

};
