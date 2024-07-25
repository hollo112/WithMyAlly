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
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"

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


    cnt = 0;
}

// Called when the game starts or when spawned
void AABItemSiren::BeginPlay()
{
	Super::BeginPlay();

  /*  if (InteractionButtonWidgetClass)
    {
        ItemWidget = CreateWidget<UUserWidget>(GetWorld(), InteractionButtonWidgetClass);

        if (ItemWidget)
        {
            ItemWidget->AddToViewport();
        }
    }*/
    FTimerHandle TimerHandle;
    float SoundTime = 1;
    GetWorldTimerManager().SetTimer(TimerHandle, this, &AABItemSiren::MakeSound, SoundTime, true);
  
    //
    //bIsVisible = false;
}

void AABItemSiren::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
    //ServerRPCOverlap(OtherActor);
}

void AABItemSiren::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    //ServerRPCOverlapEnd(OtherActor);
}

void AABItemSiren::MakeSound()
{
    const float MinSoundThreshold = 10.0f; // 예시 임계값
    const float SoundStrength = 500.0f;

    if (SoundStrength >= MinSoundThreshold) {
        AISenseHearing->ReportNoiseEvent(this, GetActorLocation(), SoundStrength, this, 3000.f, FName("Siren"));


        if (cnt < 10) {
            UGameplayStatics::SpawnSoundAtLocation(this, Clarksion, GetActorLocation());
            cnt++;
        }
    }
}

void AABItemSiren::OnInteract()
{
    //ServerRPCInteract();
    //if (!HasAuthority())
    //{
    //    //ATDTSiren();
    //    ServerRPCInteract();
    //}
    //else
    //{
    //    ATDTSiren();
    //}
    if (HasAuthority())
    {
        if (!bIsHoldOnce)
        {
            FTimerHandle TimerHandle;
            float SoundTime = 1;
            GetWorldTimerManager().SetTimer(TimerHandle, this, &AABItemSiren::MakeSound, SoundTime, true);
        }
        //ATDTSiren();
    }
   // bIsHoldOnce = true;
}

void AABItemSiren::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AABItemSiren, Siren);
    DOREPLIFETIME(AABItemSiren, CollisionBox);
    DOREPLIFETIME(AABItemSiren, Item);
    DOREPLIFETIME(AABItemSiren, bIsVisible);
}

void AABItemSiren::ATDTSiren()
{
    //if (ItemWidget->IsVisible() && !bIsHolding)
    if (bIsVisible && !bIsHolding)
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
                SetActorEnableCollision(false);
            }
        }
      

    }
    //else if (!ItemWidget->IsVisible() && bIsHolding)
    else if (!bIsVisible && bIsHolding)
    {
        if (PlayerActor)
        {
            bIsHolding = false;
            AWMACharacterPlayer* player = Cast<AWMACharacterPlayer>(PlayerActor);
            if (player)
            {
                UE_LOG(LogTemp, Log, TEXT("Log detatch"));
                Siren->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
                //DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
                Siren->SetSimulatePhysics(true);
                PlayerActor = NULL;
                SetActorEnableCollision(true);
            }
        }
        
    }
}

void AABItemSiren::ServerRPCOverlapEnd_Implementation(AActor* OtherActor)
{
    MulticastRPCOverlapEnd(OtherActor);
}

void AABItemSiren::MulticastRPCOverlapEnd_Implementation(AActor* OtherActor)
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

    //
    bIsVisible = false;
}

void AABItemSiren::ServerRPCOverlap_Implementation(AActor* OtherActor)
{
    MulticastRPCOverlap(OtherActor);
}

void AABItemSiren::MulticastRPCOverlap_Implementation(AActor* OtherActor)
{
    UE_LOG(LogTemp, Log, TEXT("overlap"));
    AWMACharacterPlayer* player = Cast<AWMACharacterPlayer>(OtherActor);

    if (player && player->IsLocallyControlled())
    {
        if (ItemWidget)
        {
            ItemWidget->SetVisibility(ESlateVisibility::Visible);
        }
    }
    PlayerActor = OtherActor;
    bIsVisible = true;
}

void AABItemSiren::ServerRPCInteract_Implementation()
{
    MulticastRPCInteract();
    //ATDTSiren();
   
}

void AABItemSiren::MulticastRPCInteract_Implementation()
{
    if (!bIsHolding)
    {
        UE_LOG(LogTemp, Log, TEXT("Log server InteractSiren"));

        if (PlayerActor)
        {
            AWMACharacterPlayer* player = Cast<AWMACharacterPlayer>(PlayerActor);
            if (player)
            {
                //AttachToComponent(player->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("RightHandSocket"));
                Siren->SetSimulatePhysics(false);

                UE_LOG(LogTemp, Log, TEXT("Log server attach"));
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

