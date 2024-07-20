// Fill out your copyright notice in the Description page of Project Settings.


#include "Trigger/WMATrain1FTrigger.h"
#include "Engine/World.h"
#include "Character/WMACharacterNonePlayer.h"


void AWMATrain1FTrigger::BeginPlay()
{
	Super::BeginPlay();
}

AWMATrain1FTrigger::AWMATrain1FTrigger()
{
	OnActorBeginOverlap.AddDynamic(this, &AWMATrain1FTrigger::SpawnActor);
	NumberOfActorsToSpawn =10;
}

void AWMATrain1FTrigger::SpawnActor(AActor* overlappedActor, AActor* otherActor)
{
	if (ActorToSpawn != nullptr)
	{
		for (int32 i = 0; i < NumberOfActorsToSpawn; ++i)
		{
			// 위치를 약간씩 변경하여 스폰할 경우 서로 겹치지 않도록 함
			FVector DesiredLocation = FVector(3320.0f , -570.0f, 50.0f);
			FRotator DesiredRotation = FRotator(0.0f, 90.0f, 0.0f);

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			// WMACharacterNonePlayer 클래스를 스폰
			GetWorld()->SpawnActor<AWMACharacterNonePlayer>(ActorToSpawn, DesiredLocation, DesiredRotation, SpawnParams);
		}
	}
}
