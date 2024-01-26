// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WMACharacterNonePlayer.h"

AWMACharacterNonePlayer::AWMACharacterNonePlayer()
{
}

void AWMACharacterNonePlayer::SetDead()
{
	Super::SetDead();

	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			Destroy();
		}
	), DeadEventDelayTime, false);
}
