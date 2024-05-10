// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ABItemPhone.h"
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

// Sets default values
AABItemPhone::AABItemPhone()
{
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Effect = CreateDefaultSubobject < UParticleSystemComponent>(TEXT("Effect"));
	Text = CreateDefaultSubobject<UWidgetComponent>(TEXT("Text"));
	Item = CreateDefaultSubobject<UABItemData>(TEXT("ItemBat"));

	static ConstructorHelpers::FClassFinder<UUserWidget>InputE(TEXT("WidgetBlueprint'/Game/UI/WBP_ItemInteractionF.WBP_ItemInteractionF_C'"));
	if (InputE.Succeeded())
	{
		InteractionItemWidgetClass = InputE.Class;
	}

	RootComponent = Trigger;
	Mesh->SetupAttachment(Trigger);
	Effect->SetupAttachment(Trigger);

	Trigger->SetCollisionProfileName(CPROFILE_WMATRIGGER);
	Trigger->SetBoxExtent(FVector(11.0f, 10.0f, 110.0f));
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AABItemPhone::OnOverlapBegin);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AABItemPhone::OnOverlapEnd);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Item/SmartPhone/smartPhone_Box001.smartPhone_Box001'"));

	if (BoxMeshRef.Object) {
		Mesh->SetStaticMesh(BoxMeshRef.Object);
	}
	Mesh->SetRelativeLocation(FVector(0.0f, -3.5f, -20.0f));
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
}

void AABItemPhone::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	if (InteractionItemWidgetClass)
	{
		ItemText = CreateWidget<UUserWidget>(GetWorld(), InteractionItemWidgetClass);

		if (ItemText)
			ItemText->AddToViewport();
	}
}

void AABItemPhone::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	if (ItemText)
	{
		ItemText->RemoveFromViewport();
		ItemText = nullptr;
	}

}

void AABItemPhone::OnEffectFinished(UParticleSystemComponent* ParticleSystem)
{
	Destroy();

}

