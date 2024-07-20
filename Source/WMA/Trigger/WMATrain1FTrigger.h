// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "Character/WMACharacterNonePlayer.h"
#include "WMATrain1FTrigger.generated.h"

/**
 * 
 */
UCLASS()
class WMA_API AWMATrain1FTrigger : public ATriggerBox
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	AWMATrain1FTrigger();

	UFUNCTION()
	void SpawnActor(class AActor* overlappedActor, class AActor* otherActor);

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class AWMACharacterNonePlayer> ActorToSpawn;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	int32 NumberOfActorsToSpawn ;
};
