// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_ThrowCheck.h"
#include "Item/WMAThrowingObject.h"
#include "Character/WMACharacterPlayer.h"

void UAnimNotify_ThrowCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	//UE_LOG(LogTemp, Log, TEXT("Log Thorwing Notify"));
	UWorld* world = MeshComp->GetWorld();
	
	FName path = TEXT("/Script/Engine.Blueprint'/Game/Blueprint/BP_WMAThrowingObject.BP_WMAThrowingObject'");
	UBlueprint* ObjectToSpawn = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), NULL, *path.ToString()));
	FActorSpawnParameters spawnParams;
	FRotator rotator = MeshComp->GetSocketRotation(TEXT("ThrowSocket"));
	rotator.Yaw = rotator.Yaw - 60;
	rotator.Pitch = rotator.Pitch - 140;
	rotator.Roll = rotator.Roll;
	FVector spawnLocation = MeshComp->GetSocketLocation(TEXT("ThrowSocket"));
	world->SpawnActor<AActor>(ObjectToSpawn->GeneratedClass, spawnLocation, rotator, spawnParams);
	//world->SpawnActor<AWMAThrowingObject>(spawnLocation, rotator);

	/*AWMACharacterPlayer* player = Cast<AWMACharacterPlayer>(MeshComp->GetOwner());
	player->HideThrowItem();*/
}
