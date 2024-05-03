// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/WMAGameState.h"
#include "WMA.h"
#include "Net/UnrealNetwork.h"

void AWMAGameState::HandleBeginPlay()
{
	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("Begin"));

	Super::HandleBeginPlay();

	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("End"));
}

void AWMAGameState::OnRep_ReplicatedHasBegunPlay()
{
	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("Begin"));

	Super::OnRep_ReplicatedHasBegunPlay();

	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("End"));
}