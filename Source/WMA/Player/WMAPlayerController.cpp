// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/WMAPlayerController.h"

void AWMAPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}
