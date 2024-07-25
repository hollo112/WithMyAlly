// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_FiringRifleCheck.h"
#include "Item/ABItemBullet.h"
#include "Character/WMACharacterPlayer.h"

void UAnimNotify_FiringRifleCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	//UE_LOG(LogTemp, Log, TEXT("Log Thorwing Notify"));
	UWorld* world = MeshComp->GetWorld();

	FName path = TEXT("/Script/Engine.Blueprint'/Game/Blueprint/BulletActor.BulletActor'");
	UBlueprint* ObjectToSpawn = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), NULL, *path.ToString()));
	FActorSpawnParameters spawnParams;
	FRotator rotator = MeshComp->GetSocketRotation(TEXT("BulletSocket"));
	rotator.Yaw = rotator.Yaw-90;
	rotator.Pitch = rotator.Pitch;
	rotator.Roll = rotator.Roll;
	FVector spawnLocation = MeshComp->GetSocketLocation(TEXT("BulletSocket"));
	//world->SpawnActor<AActor>(ObjectToSpawn->GeneratedClass, spawnLocation, rotator, spawnParams);
	//world->SpawnActor<AWMAThrowingObject>(spawnLocation, rotator);
	world->SpawnActor<AABItemBullet>(spawnLocation, rotator);
	//AWMACharacterPlayer* player = Cast<AWMACharacterPlayer>(MeshComp->GetOwner());
	//player->HideThrowItem();
}
