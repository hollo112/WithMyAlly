// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ABThorwItem.h"
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
AABThorwItem::AABThorwItem()
{
    Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh1"));
    Effect = CreateDefaultSubobject < UParticleSystemComponent>(TEXT("Effect"));
    TextE = CreateDefaultSubobject<UWidgetComponent>(TEXT("TextE"));
    Item = CreateDefaultSubobject<UABItemData>(TEXT("ThrowItem"));

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));


    static ConstructorHelpers::FClassFinder<UUserWidget>InputE(TEXT("/Game/UI/WBP_ItemInteraction.WBP_ItemInteraction_C"));
    if (InputE.Succeeded())
    {
        InteractionItemWidgetClass = InputE.Class;
    }

    RootComponent = Trigger;
    Mesh->SetupAttachment(Trigger);
    Effect->SetupAttachment(Trigger);
    StaticMeshComponent = Mesh;
    StaticMeshComponent->SetupAttachment(Trigger);

    StaticMeshComponent->OnComponentHit.AddDynamic(this, &AABThorwItem::OnHit);

    Trigger->SetCollisionProfileName(CPROFILE_WMATRIGGER);
    Trigger->SetBoxExtent(FVector(11.0f, 10.0f, 110.0f));

    Trigger->OnComponentBeginOverlap.AddDynamic(this, &AABThorwItem::OnOverlapBegin);
    Trigger->OnComponentEndOverlap.AddDynamic(this, &AABThorwItem::OnOverlapEnd);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshRef1(TEXT("/Script/Engine.StaticMesh'/Game/Item/Samdasoo/samdasoo1.samdasoo1'"));
    if (BoxMeshRef1.Succeeded())
    {
        Mesh->SetStaticMesh(BoxMeshRef1.Object);
    }

    Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    Mesh->SetCollisionProfileName(TEXT("NoCollision"));


    Mesh->SetIsReplicated(true);

}

// Called when the game starts or when spawned
void AABThorwItem::BeginPlay()
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

void AABThorwItem::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    //if (ImpactSound)
    //{
    //    UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
    //}
}

void AABThorwItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
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

void AABThorwItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
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

void AABThorwItem::OnEffectFinished(UParticleSystemComponent* ParticleSystem)
{
    Destroy();
}

void AABThorwItem::OnInteract()
{
    if (ItemWidget->IsVisible())
    {
        UE_LOG(LogTemp, Warning, TEXT("ItemWidget is visible"));
        if (nullptr == Item) {
            Destroy();
            return;
        }

        if (PlayerActor)
        {
            UE_LOG(LogTemp, Warning, TEXT("PlayerActor is valid"));
            IABCharacterItemInterface* OverlappingPawn = Cast<IABCharacterItemInterface>(PlayerActor);
            if (OverlappingPawn)
            {
                UE_LOG(LogTemp, Warning, TEXT("OverlappingPawn is valid"));
                OverlappingPawn->TakeItem(Item);
            }
        }
        Mesh->SetHiddenInGame(true);
        SetActorEnableCollision(false);
        Effect->OnSystemFinished.AddDynamic(this, &AABThorwItem::OnEffectFinished);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ItemWidget is not visible"));
    }
}