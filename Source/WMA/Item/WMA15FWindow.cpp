// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/WMA15FWindow.h"

// Sets default values
AWMA15FWindow::AWMA15FWindow()
{
	EmptyScene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	EmptyScene->SetupAttachment(RootComponent);

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	DoorFrame->SetupAttachment(EmptyScene);
}

// Called when the game starts or when spawned
void AWMA15FWindow::BeginPlay()
{
	Super::BeginPlay();
	
}

