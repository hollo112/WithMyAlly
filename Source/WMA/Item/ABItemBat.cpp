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
#include "Character/WMACharacterPlayer.h"

// Sets default values
AABItemBat::AABItemBat()
{
    Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Effect = CreateDefaultSubobject < UParticleSystemComponent>(TEXT("Effect"));
    TextE = CreateDefaultSubobject<UWidgetComponent>(TEXT("TextE"));
    Item = CreateDefaultSubobject<UABItemData>(TEXT("ItemBat"));



    static ConstructorHelpers::FClassFinder<UUserWidget>InputE(TEXT("/Game/UI/WBP_ItemInteraction.WBP_ItemInteraction_C"));
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
    Trigger->OnComponentEndOverlap.AddDynamic(this, &AABItemBat::OnOverlapEnd);


    static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Item/Bat/Batfbx.Batfbx'"));
    if (BoxMeshRef.Succeeded())
    {
        TempBoxMesh = BoxMeshRef.Object;
        Mesh->SetStaticMesh(BoxMeshRef.Object);
    }
    Mesh->SetRelativeLocation(FVector(0.0f, -3.5f, -20.0f));
    Mesh->SetCollisionProfileName(TEXT("NoCollision"));


    Mesh->SetIsReplicated(true);
}

void AABItemBat::BeginPlay()
{
    Super::BeginPlay();

    if (InteractionItemWidgetClass)
    {
        ItemWidget = CreateWidget<UUserWidget>(GetWorld(), InteractionItemWidgetClass);
        
        if (ItemWidget)
        {
            ItemWidget->AddToViewport();
        }
    }
}

void AABItemBat::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
    AWMACharacterPlayer* player = Cast<AWMACharacterPlayer>(OtherActor);
    if (player && player->IsLocallyControlled())
    {
        if (ItemWidget)
        {
            ItemWidget->SetVisibility(ESlateVisibility::Visible);
            PlayerActor = OtherActor;
        }
    }
}

void AABItemBat::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    AWMACharacterPlayer* player = Cast<AWMACharacterPlayer>(OtherActor);

    if (player && player->IsLocallyControlled())
    {
        if (ItemWidget && player->IsLocallyControlled())
        {
            ItemWidget->SetVisibility(ESlateVisibility::Hidden);
            PlayerActor = NULL;
        }
    }
}

void AABItemBat::OnEffectFinished(UParticleSystemComponent* ParticleSystem)
{
    Destroy();
}

void AABItemBat::OnInteract()
{
    if (ItemWidget->IsVisible())
    {
        if (nullptr == Item) {
            Destroy();
            return;
        }

        if (PlayerActor)
        {
            IABCharacterItemInterface* OverlappingPawn = Cast<IABCharacterItemInterface>(PlayerActor);
            if (OverlappingPawn)
            {
                OverlappingPawn->TakeItem(Item);
            }
        }
        Mesh->SetHiddenInGame(true);
        SetActorEnableCollision(false);
        Effect->OnSystemFinished.AddDynamic(this, &AABItemBat::OnEffectFinished);
    }
    ////Effect->Activate(true);
}
