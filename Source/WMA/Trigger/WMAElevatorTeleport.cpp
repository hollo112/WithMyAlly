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
		if (otherTele)
		{
			AWMACharacterPlayer* player = Cast<AWMACharacterPlayer>(otherActor);
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
