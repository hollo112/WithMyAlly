// Fill out your copyright notice in the Description page of Project Settings.


#include "Trigger/WMAElevatorTeleport.h"

void AWMAElevatorTeleport::BeginPlay()
{
	Super::BeginPlay();
}

AWMAElevatorTeleport::AWMAElevatorTeleport()
{
	OnActorBeginOverlap.AddDynamic(this, &AWMAElevatorTeleport::EnterTeleporter);
	OnActorEndOverlap.AddDynamic(this, &AWMAElevatorTeleport::ExitTeleporter);
	teleporting = false;
}

void AWMAElevatorTeleport::EnterTeleporter(AActor* overlappedActor, AActor* otherActor)
{
	if (otherActor && otherActor != this)
	{
		AWMACharacterPlayer* player = Cast<AWMACharacterPlayer>(otherActor);
		bPlayerIn = true;
		//WaitForPlayerInteract(otherActor);
		if (otherTele)
		{
			if (player && !otherTele->teleporting)
			{
				teleporting = true;
				player->SetActorRotation(otherTele->GetActorRotation());
				player->GetController()->SetControlRotation(player->GetActorRotation());
				player->SetActorLocation(otherTele->GetActorLocation());
			}
		}
	}
}

void AWMAElevatorTeleport::ExitTeleporter(AActor* overlappedActor, AActor* otherActor)
{
	if (otherActor && otherActor != this)
	{
		bPlayerIn = false;
		if (otherTele && !teleporting)
		{
			AWMACharacterPlayer* player = Cast<AWMACharacterPlayer>(otherActor);
			if (player && !otherTele->teleporting)
			{
				otherTele->teleporting = false;
			}
		}
	}
}

void AWMAElevatorTeleport::WaitForPlayerInteract(AActor* Player)
{
	AWMACharacterPlayer* player = Cast<AWMACharacterPlayer>(Player);
	while (bPlayerIn)
	{
		UE_LOG(LogTemp, Log, TEXT("playerIn"));
		if (player->bInteract)
		{
			if (otherTele)
			{
				if (player && !otherTele->teleporting)
				{
					teleporting = true;
					player->SetActorRotation(otherTele->GetActorRotation());
					player->GetController()->SetControlRotation(player->GetActorRotation());
					player->SetActorLocation(otherTele->GetActorLocation());
				}
			}
		}
	}
}
