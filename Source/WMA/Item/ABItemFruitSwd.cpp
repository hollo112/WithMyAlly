// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ABItemFruitSwd.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Physics/WMACollsion.h"
#include "Interface/ABCharacterItemInterface.h"

// Sets default values
AABItemFruitSwd::AABItemFruitSwd()
{
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Effect = CreateDefaultSubobject < UParticleSystemComponent>(TEXT("Effect"));

	RootComponent = Trigger;
	Mesh->SetupAttachment(Trigger);
	Effect->SetupAttachment(Trigger);

	Trigger->SetCollisionProfileName(CPROFILE_WMATRIGGER);
	Trigger->SetBoxExtent(FVector(11.0f, 10.0f, 110.0f));
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AABItemFruitSwd::OnOverlapBegin);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Item/FruitSword/FruitSwdFbx.FruitSwdFbx'"));

	if (BoxMeshRef.Object) {
		Mesh->SetStaticMesh(BoxMeshRef.Object);
	}
	Mesh->SetRelativeLocation(FVector(0.0f, -3.5f, -20.0f));
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
}

void AABItemFruitSwd::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	if (nullptr == Item) {
		Destroy();
		return;
	}

	IABCharacterItemInterface* OverlappingPawn = Cast<IABCharacterItemInterface>(OtherActor);
	if (OverlappingPawn) {
		OverlappingPawn->TakeItem(Item);
	}

	Mesh->SetHiddenInGame(true);
	SetActorEnableCollision(false);
	Effect->OnSystemFinished.AddDynamic(this, &AABItemFruitSwd::OnEffectFinished);

}

void AABItemFruitSwd::OnEffectFinished(UParticleSystemComponent* ParticleSystem)
{
	Destroy();

}