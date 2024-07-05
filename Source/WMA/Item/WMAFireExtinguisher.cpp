// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/WMAFireExtinguisher.h"
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
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AWMAFireExtinguisher::AWMAFireExtinguisher()
{
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(FName("CollisionBox"));

    CollisionBox->SetCollisionProfileName(CPROFILE_WMATRIGGER);
    CollisionBox->SetBoxExtent(FVector(110.0f, 100.0f, 110.0f));
    FireExt = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FireExt"));
    FireExt->SetCollisionProfileName("NoCollision");
    //RootComponent = Siren;
    FireExt->SetupAttachment(RootComponent);
    CollisionBox->SetupAttachment(FireExt);

    //Niagara
    SmokeSystem = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/Niagara/NewNiagaraSystem.NewNiagaraSystem"));
    NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Smoke"));
    NiagaraComp->SetAsset(SmokeSystem);
    NiagaraComp->SetupAttachment(FireExt);

    //Widget
    static ConstructorHelpers::FClassFinder<UUserWidget>InputE(TEXT("/Game/UI/WBP_ItemInteraction.WBP_ItemInteraction_C"));
    if (InputE.Succeeded())
    {
        UE_LOG(LogTemp, Log, TEXT("Createwidget"));
        InteractionButtonWidgetClass = InputE.Class;
    }

    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AWMAFireExtinguisher::OnOverlapBegin);
    CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AWMAFireExtinguisher::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AWMAFireExtinguisher::BeginPlay()
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

    NiagaraComp->Deactivate();
    //
    bIsVisible = false;
}

void AWMAFireExtinguisher::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
    ServerRPCOverlap(OtherActor);
}

void AWMAFireExtinguisher::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    ServerRPCOverlapEnd(OtherActor);
}

void AWMAFireExtinguisher::OnInteract()
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
        ATDTFireExt();
    }
    bIsHoldOnce = true;
}

void AWMAFireExtinguisher::TurnOnFireExt()
{
    if (!bTurnOn)
    {
        bTurnOn = true;
        NiagaraComp->Activate();
        UE_LOG(LogTemp, Log, TEXT("Log click"));
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("Log false"));
        bTurnOn = false;
        NiagaraComp->Deactivate();
    }
}

void AWMAFireExtinguisher::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AWMAFireExtinguisher, FireExt);
    DOREPLIFETIME(AWMAFireExtinguisher, CollisionBox);
    DOREPLIFETIME(AWMAFireExtinguisher, Item);
    DOREPLIFETIME(AWMAFireExtinguisher, bIsVisible);
}

void AWMAFireExtinguisher::ATDTFireExt()
{
    //if (ItemWidget->IsVisible() && !bIsHolding)
    if (bIsVisible && !bIsHolding)
    {
        UE_LOG(LogTemp, Log, TEXT("Log InteractFireExt"));

        if (PlayerActor)
        {
            AWMACharacterPlayer* player = Cast<AWMACharacterPlayer>(PlayerActor);
            if (player)
            {
                //AttachToComponent(player->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("RightHandSocket"));
                FireExt->SetSimulatePhysics(false);

                UE_LOG(LogTemp, Log, TEXT("Log attach"));
                bIsHolding = true;
                FireExt->AttachToComponent(player->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RightHandSocket"));
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
                FireExt->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
                //DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
                FireExt->SetSimulatePhysics(true);
                PlayerActor = NULL;
                SetActorEnableCollision(true);
            }
        }

    }
}

void AWMAFireExtinguisher::ServerRPCOverlapEnd_Implementation(AActor* OtherActor)
{
    MulticastRPCOverlapEnd(OtherActor);
}

void AWMAFireExtinguisher::MulticastRPCOverlapEnd_Implementation(AActor* OtherActor)
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

void AWMAFireExtinguisher::ServerRPCOverlap_Implementation(AActor* OtherActor)
{
    MulticastRPCOverlap(OtherActor);
}

void AWMAFireExtinguisher::MulticastRPCOverlap_Implementation(AActor* OtherActor)
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

void AWMAFireExtinguisher::ServerRPCInteract_Implementation()
{
    MulticastRPCInteract();
    //ATDTSiren();

}

void AWMAFireExtinguisher::MulticastRPCInteract_Implementation()
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
                FireExt->SetSimulatePhysics(false);

                UE_LOG(LogTemp, Log, TEXT("Log server attach"));
                bIsHolding = true;
                FireExt->AttachToComponent(player->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("RightHandSocket"));
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
                FireExt->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
                //DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
                FireExt->SetSimulatePhysics(true);
                PlayerActor = NULL;
            }
        }
        SetActorEnableCollision(true);
    }
}

