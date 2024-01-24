// Fill out your copyright notice in the Description page of Project Settings.


#include "ABItemBat.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "WithMyAlly/Physics/ABCollision.h"
#include "/Unreal Projects/WithMyAlly/Source/WithMyAlly/Interface/ABCharacterItemInterface.h"

// Sets default values
AABItemBat::AABItemBat()
{

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Effect = CreateDefaultSubobject < UParticleSystemComponent>(TEXT("Effect"));

	RootComponent = Trigger;
	Mesh->SetupAttachment(Trigger);
	Effect->SetupAttachment(Trigger);

	Trigger->SetCollisionProfileName(CPROFILE_ABTRIGGER);
	Trigger->SetBoxExtent(FVector(11.0f, 10.0f, 110.0f));
	Trigger->OnComponentBeginOverlap.AddDynamic(this,&AABItemBat::OnOverlapBegin);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Item/Bat_fin/Geometries/Cylinder001.Cylinder001'"));
	if (BoxMeshRef.Object) {
		Mesh->SetStaticMesh(BoxMeshRef.Object);
	}
	Mesh->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));
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

	Mesh->SetHiddenInGame(true);
	SetActorEnableCollision(false);
	Effect->OnSystemFinished.AddDynamic(this, &AABItemBat::OnEffectFinished);

}

void AABItemBat::OnEffectFinished(UParticleSystemComponent* ParticleSystem)
{
	Destroy();
}

