// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorEVActor.h"

// Sets default values
ADoorEVActor::ADoorEVActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EmptyScene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	EmptyScene->SetupAttachment(RootComponent);

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	DoorFrame->SetupAttachment(EmptyScene);
}

// Called when the game starts or when spawned
void ADoorEVActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoorEVActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


