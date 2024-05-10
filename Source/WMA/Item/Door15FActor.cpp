// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Door15FActor.h"

// Sets default values
ADoor15FActor::ADoor15FActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	DoorFrame->SetupAttachment(RootComponent);

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	DoorFrame->SetupAttachment(DoorFrame);
}

// Called when the game starts or when spawned
void ADoor15FActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor15FActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

