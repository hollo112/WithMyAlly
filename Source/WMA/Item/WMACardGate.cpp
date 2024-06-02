// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/WMACardGate.h"

// Sets default values
AWMACardGate::AWMACardGate()
{
	EmptyScene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	EmptyScene->SetupAttachment(RootComponent);

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	DoorFrame->SetupAttachment(EmptyScene);
}

// Called when the game starts or when spawned
void AWMACardGate::BeginPlay()
{
	Super::BeginPlay();
	
}

