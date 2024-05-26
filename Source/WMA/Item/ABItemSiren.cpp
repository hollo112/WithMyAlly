// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ABItemSiren.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Physics/WMACollsion.h"
#include "Interface/ABCharacterItemInterface.h"
#include <GameData/WMAGameInstance.h>
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "UI/WMAItemInteractionWidget.h"
#include "Interface/ABCharacterItemInterface.h"
#include "Character/WMACharacterPlayer.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AABItemSiren::AABItemSiren()
{
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(FName("CollisionBox"));
  
    CollisionBox->SetCollisionProfileName(CPROFILE_WMATRIGGER);
    CollisionBox->SetBoxExtent(FVector(110.0f, 100.0f, 110.0f));
    Siren = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Siren"));
    Siren->SetCollisionProfileName("NoCollision");
    //RootComponent = Siren;
    Siren->SetupAttachment(RootComponent);
    CollisionBox->SetupAttachment(Siren);
    //Widget
    static ConstructorHelpers::FClassFinder<UUserWidget>InputE(TEXT("/Game/UI/WBP_ItemInteraction.WBP_ItemInteraction_C"));
    if (InputE.Succeeded())
    {
        UE_LOG(LogTemp, Log, TEXT("Createwidget"));
        InteractionButtonWidgetClass = InputE.Class;
    }

    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AABItemSiren::OnOverlapBegin);
    CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AABItemSiren::OnOverlapEnd);

}

// Called when the game starts or when spawned
void AABItemSiren::BeginPlay()
{
	Super::BeginPlay();

    if (InteractionButtonWidgetClass)
    {
        ItemWidget = CreateWidget<UUserWidget>(GetWorld(), InteractionButtonWidgetClass);

        if (ItemWidget)
        {
            ItemWidget->AddToViewport();
        }
    }

    FTimerHandle TimerHandle;
    float SoundTime = 1;
    GetWorldTimerManager().SetTimer(TimerHandle, this, &AABItemSiren::MakeSound, SoundTime, true);
}

void AABItemSiren::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
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

void AABItemSiren::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    AWMACharacterPlayer* player = Cast<AWMACharacterPlayer>(OtherActor);

    if (player && player->IsLocallyControlled())
    {
        if (ItemWidget && player->IsLocallyControlled())
        {
            ItemWidget->SetVisibility(ESlateVisibility::Hidden);
            //PlayerActor = NULL;
        }
    }
}

void AABItemSiren::MakeSound()
{
    const float MinSoundThreshold = 50.0f; // 예시 임계값
    const float SoundStrength = 120.0f;

    if (SoundStrength >= MinSoundThreshold) {
        AISenseHearing->ReportNoiseEvent(this, GetActorLocation(), SoundStrength, this, 30.0f, FName("Siren"));
    }
}

void AABItemSiren::OnInteract()
{
    //ServerRPCInteract();
    if (!HasAuthority())
    {
        //ATDTSiren();
        ServerRPCInteract();
    }
    else
    {
        ATDTSiren();
    }
}

void AABItemSiren::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AABItemSiren, Siren);
    DOREPLIFETIME(AABItemSiren, CollisionBox);
    DOREPLIFETIME(AABItemSiren, Item);
}

void AABItemSiren::ATDTSiren()
{
    if (ItemWidget->IsVisible() && !bIsHolding)
    {
        UE_LOG(LogTemp, Log, TEXT("Log InteractSiren"));

        if (PlayerActor)
        {
            AWMACharacterPlayer* player = Cast<AWMACharacterPlayer>(PlayerActor);
            if (player)
            {
                //AttachToComponent(player->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("RightHandSocket"));
                Siren->SetSimulatePhysics(false);

                UE_LOG(LogTemp, Log, TEXT("Log attach"));
                bIsHolding = true;
                Siren->AttachToComponent(player->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RightHandSocket"));
            }
        }
        SetActorEnableCollision(false);

    }
    else if (!ItemWidget->IsVisible() && bIsHolding)
    {
        bIsHolding = false;
        if (PlayerActor)
        {
            AWMACharacterPlayer* player = Cast<AWMACharacterPlayer>(PlayerActor);
            if (player)
            {
                UE_LOG(LogTemp, Log, TEXT("Log detatch"));
                Siren->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
                //DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
                Siren->SetSimulatePhysics(true);
                PlayerActor = NULL;
            }
        }
        SetActorEnableCollision(true);
    }
}

void AABItemSiren::ServerRPCInteract_Implementation()
{
    //MulticastRPCInteract();
    //ATDTSiren();
    if (!bIsHolding)
    {
        UE_LOG(LogTemp, Log, TEXT("Log InteractSiren"));

        if (PlayerActor)
        {
            AWMACharacterPlayer* player = Cast<AWMACharacterPlayer>(PlayerActor);
            if (player)
            {
                //AttachToComponent(player->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("RightHandSocket"));
                Siren->SetSimulatePhysics(false);

                UE_LOG(LogTemp, Log, TEXT("Log attach"));
                bIsHolding = true;
                Siren->AttachToComponent(player->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RightHandSocket"));
            }
        }
        SetActorEnableCollision(false);

    }
    else if (!ItemWidget->IsVisible() && bIsHolding)
    {
        bIsHolding = false;
        if (PlayerActor)
        {
            AWMACharacterPlayer* player = Cast<AWMACharacterPlayer>(PlayerActor);
            if (player)
            {
                UE_LOG(LogTemp, Log, TEXT("Log detatch"));
                Siren->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
                //DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
                Siren->SetSimulatePhysics(true);
                PlayerActor = NULL;
            }
        }
        SetActorEnableCollision(true);
    }
}

void AABItemSiren::MulticastRPCInteract_Implementation()
{
   
}

