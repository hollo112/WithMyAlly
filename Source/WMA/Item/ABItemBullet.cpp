// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ABItemBullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Physics/WMACollsion.h"
#include "Interface/ABCharacterItemInterface.h"
#include <GameData/WMAGameInstance.h>
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "UI/WMAItemInteractionWidget.h"
#include "Interface/ABCharacterItemInterface.h"
#include "Character/WMACharacterPlayer.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AABItemBullet::AABItemBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


}

// Called when the game starts or when spawned
void AABItemBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AABItemBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}
