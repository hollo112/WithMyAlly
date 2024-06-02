// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WMACardGate.generated.h"

UCLASS()
class WMA_API AWMACardGate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWMACardGate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* DoorFrame;


	UPROPERTY(VisibleAnywhere)
	USceneComponent* EmptyScene;
};
