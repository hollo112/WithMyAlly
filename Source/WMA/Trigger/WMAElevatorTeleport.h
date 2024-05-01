// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "GameFramework/Actor.h"
#include "Character/WMACharacterPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "WMAElevatorTeleport.generated.h"


/**
 * 
 */
UCLASS()
class WMA_API AWMAElevatorTeleport : public ATriggerBox
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	AWMAElevatorTeleport();

	UFUNCTION()
	void EnterTeleporter(class AActor* overlappedActor, class AActor* otherActor);

	UFUNCTION()
	void ExitTeleporter(class AActor* overlappedActor, class AActor* otherActor);

	UPROPERTY(EditAnywhere, Category = "Teleporter")
	AWMAElevatorTeleport* otherTele;
	UPROPERTY()
	bool teleporting;
};
