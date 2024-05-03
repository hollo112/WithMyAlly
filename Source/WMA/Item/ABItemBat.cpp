// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ABItemBat.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Physics/WMACollsion.h"
#include "Interface/ABCharacterItemInterface.h"
#include "Character/WMACharacterPlayer.h"
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
	if (InputE.Succeeded()) {
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
	if (BoxMeshRef.Succeeded()) {
		TempBoxMesh = BoxMeshRef.Object;
		Mesh->SetStaticMesh(BoxMeshRef.Object);
	}
	Mesh->SetRelativeLocation(FVector(0.0f, -3.5f, -20.0f));
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));


	bInteractionItem = false;
	

	PrimaryActorTick.bCanEverTick = true;
}

void AABItemBat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("Character is Die :: %s"), bInteractionItem ? TEXT("true") : TEXT("false"));

	if (bInteractionItem) {
		Trigger->OnComponentBeginOverlap.AddDynamic(this, &AABItemBat::OnOverlapBegin);
		UE_LOG(LogTemp,Warning,TEXT("NO item Attach"))
	}
}

void AABItemBat::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	//TextE->SetHiddenInGame(false);

	if (InteractionItemWidgetClass) {
		ItemText = CreateWidget<UUserWidget>(GetWorld(), InteractionItemWidgetClass);

		if(ItemText)
			ItemText->AddToViewport();
	}

	if (nullptr == Item) {
		Destroy();
		return;
	 }

	//UE_LOG(LogTemp, Warning, TEXT("Character is Die :: %s"), bInteractionItem ? TEXT("true") : TEXT("false"));

	if (bInteractionItem) {
		IABCharacterItemInterface* OverlappingPawn = Cast<IABCharacterItemInterface>(OtherActor);
		if (OverlappingPawn) {
			OverlappingPawn->TakeItem(Item);
			//TextE->SetHiddenInGame(true);
		}

		//Effect->Activate(true);
		Mesh->SetHiddenInGame(true);
		SetActorEnableCollision(false);



		Effect->OnSystemFinished.AddDynamic(this, &AABItemBat::OnEffectFinished);

		Trigger->OnComponentBeginOverlap.RemoveDynamic(this, &AABItemBat::OnOverlapBegin);
	}
}

void AABItemBat::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	if (ItemText) {
		ItemText->RemoveFromViewport();
		ItemText = nullptr;
	}

}

void AABItemBat::OnEffectFinished(UParticleSystemComponent* ParticleSystem)
{
	Destroy();
}

void AABItemBat::StartInteractionItem()
{
	bInteractionItem = true;
}

void AABItemBat::StopInteractionItem()
{
	//bInteractionItem = false;
}

