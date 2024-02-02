// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ABItemBat.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Physics/WMACollsion.h"
#include "Interface/ABCharacterItemInterface.h"

// Sets default values
AABItemBat::AABItemBat()
{
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Effect = CreateDefaultSubobject < UParticleSystemComponent>(TEXT("Effect"));

	RootComponent = Trigger;
	Mesh->SetupAttachment(Trigger);
	Effect->SetupAttachment(Trigger);

	Trigger->SetCollisionProfileName(CPROFILE_WMATRIGGER);
	Trigger->SetBoxExtent(FVector(11.0f, 10.0f, 110.0f));
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AABItemBat::OnOverlapBegin);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Item/Bat/Batfbx.Batfbx'"));

	if (BoxMeshRef.Object) {
		Mesh->SetStaticMesh(BoxMeshRef.Object);
	}
	Mesh->SetRelativeLocation(FVector(0.0f, -3.5f, -20.0f));
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
}

void AABItemBat::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	if (nullptr == Item) {
		Destroy();
		return;
	}

	IABCharacterItemInterface* OverlappingPawn = Cast<IABCharacterItemInterface>(OtherActor);
	if (OverlappingPawn) {
		OverlappingPawn->TakeItem(Item);
	}

	//Effect->Activate(true);
	Mesh->SetHiddenInGame(true);
	SetActorEnableCollision(false);

	Effect->OnSystemFinished.AddDynamic(this, &AABItemBat::OnEffectFinished);
}

void AABItemBat::OnEffectFinished(UParticleSystemComponent* ParticleSystem)
{
	Destroy();
}
