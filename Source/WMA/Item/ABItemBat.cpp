// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ABItemBat.h"
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
AABItemBat::AABItemBat()
{
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Effect = CreateDefaultSubobject < UParticleSystemComponent>(TEXT("Effect"));
	TextE = CreateDefaultSubobject<UWidgetComponent>(TEXT("TextE"));
	Item = CreateDefaultSubobject<UABItemData>(TEXT("ItemBat"));



	static ConstructorHelpers::FClassFinder<UUserWidget>InputE(TEXT("WidgetBlueprint'/Game/UI/WBP_ItemInteraction.WBP_ItemInteraction_C'"));
	if (InputE.Succeeded()) 
	{
		InteractionItemWidgetClass = InputE.Class;
	}

	RootComponent = Trigger;
	Mesh->SetupAttachment(Trigger);
	Effect->SetupAttachment(Trigger);

	Trigger->SetCollisionProfileName(CPROFILE_WMATRIGGER);
	Trigger->SetBoxExtent(FVector(11.0f, 10.0f, 110.0f));

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AABItemBat::OnOverlapBegin);
	Trigger->OnComponentEndOverlap.AddDynamic(this,&AABItemBat::OnOverlapEnd);


	static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Item/Bat/Batfbx.Batfbx'"));
	if (BoxMeshRef.Succeeded()) 
	{
		TempBoxMesh = BoxMeshRef.Object;
		Mesh->SetStaticMesh(BoxMeshRef.Object);
	}
	Mesh->SetRelativeLocation(FVector(0.0f, -3.5f, -20.0f));
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
}


void AABItemBat::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	//TextE->SetHiddenInGame(false);


	UE_LOG(LogTemp, Warning, TEXT("HI"));
	if (InteractionItemWidgetClass)
	{
		ItemText = CreateWidget<UUserWidget>(GetWorld(), InteractionItemWidgetClass);

		if(ItemText)
			ItemText->AddToViewport();
	}
	if (nullptr == Item) {
		Destroy();
		return;
	}

	//IABCharacterItemInterface* OverlappingPawn = Cast<IABCharacterItemInterface>(OtherActor);
	//if (OverlappingPawn)
	//{
	//	IACharcterII = OverlappingPawn;
	//	OverlappingPawn->TakeItem(Item);

	//	//TextE->SetHiddenInGame(true);
	//	bBat = 1;
	//	UE_LOG(LogTemp, Warning, TEXT("bBat is :: %s at Begin"), bBat ? TEXT("true") : TEXT("false"));
	//}

	////Effect->Activate(true);

	//Mesh->SetHiddenInGame(true);
	//SetActorEnableCollision(false);

	//Effect->OnSystemFinished.AddDynamic(this, &AABItemBat::OnEffectFinished);
	//UE_LOG(LogTemp, Warning, TEXT("Bye"));

}

void AABItemBat::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	if (ItemText) 
	{
		ItemText->RemoveFromViewport();
		ItemText = nullptr;
	}

}

void AABItemBat::OnEffectFinished(UParticleSystemComponent* ParticleSystem)
{
	Destroy();
}
