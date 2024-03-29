// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/WMAPlayerController.h"
#include "GameFramework/GameModeBase.h"
#include "WMA.h"

AWMAPlayerController::AWMAPlayerController()
{
}

void AWMAPlayerController::PostInitializeComponents()
{
	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("Begin"));
	
	Super::PostInitializeComponents();
	
	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("End"));
}

void AWMAPlayerController::PostNetInit()
{
	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("Begin"));

	Super::PostNetInit();

	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("End"));
}

void AWMAPlayerController::BeginPlay()
{
	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("Begin"));
	AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();

	if (GameMode)
	{
		WMA_LOG(LogWMANetwork, Log, TEXT("GameMode : %s"), *GameMode->GetName());
	}
	else
	{
		WMA_LOG(LogWMANetwork, Log, TEXT("GameMode : %s"), TEXT("nullptr"));
	}

	Super::BeginPlay();

	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("End"));

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}

void AWMAPlayerController::OnPossess(APawn* InPawn)
{
	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("Begin"));

	Super::OnPossess(InPawn);

	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("End"));
}
