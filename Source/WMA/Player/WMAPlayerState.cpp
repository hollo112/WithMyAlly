// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/WMAPlayerState.h"
#include "WMA.h"
#include "Net/UnrealNetwork.h"

void AWMAPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWMAPlayerState, bFemale);
}
