// Fill out your copyright notice in the Description page of Project Settings.


#include "Trigger/WMASirenSpawner.h"
#include "Components/BoxComponent.h"
#include "Physics/WMACollsion.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "UI/WMAItemInteractionWidget.h"
#include "Character/WMACharacterPlayer.h"
#include "Net/UnrealNetwork.h"
#include "Item/ABItemSiren.h"

// Sets default values
AWMASirenSpawner::AWMASirenSpawner()
{
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(FName("CollisionBox"));

    CollisionBox->SetCollisionProfileName(CPROFILE_WMATRIGGER);
    CollisionBox->SetBoxExtent(FVector(110.0f, 100.0f, 110.0f));
    CollisionBox->SetupAttachment(RootComponent);
    //Widget
    static ConstructorHelpers::FClassFinder<UUserWidget>InputE(TEXT("/Game/UI/WBP_ItemInteraction.WBP_ItemInteraction_C"));
    if (InputE.Succeeded())
    {
        UE_LOG(LogTemp, Log, TEXT("Createwidget"));
        InteractionButtonWidgetClass = InputE.Class;
    }
    CollisionBox->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));

    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AWMASirenSpawner::OnOverlapBegin);
    CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AWMASirenSpawner::OnOverlapEnd);

}

// Called when the game starts or when spawned
void AWMASirenSpawner::BeginPlay()
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

    //
    bIsVisible = false;
}

void AWMASirenSpawner::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
    AWMACharacterPlayer* player = Cast<AWMACharacterPlayer>(OtherActor);
    if (player && player->IsLocallyControlled())
    {
        if (!bIsHoldOnce)
        {
            if (ItemWidget)
            {
                ItemWidget->SetVisibility(ESlateVisibility::Visible);
                PlayerActor = OtherActor;
            }
        }
    }
}

void AWMASirenSpawner::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
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

void AWMASirenSpawner::OnInteract()
{
   
    if (HasAuthority())
    {
        if (!bIsHoldOnce)
        {
            //ServerRPCSpawn();
            UWorld* world = GetWorld();

            //FName path = TEXT("/Script/Engine.Blueprint'/Game/Blueprint/BP_ItemSiren.BP_ItemSiren'");
            //UBlueprint* ObjectToSpawn = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), NULL, *path.ToString()));
            //FActorSpawnParameters spawnParams;
            //world->SpawnActor<AActor>(ObjectToSpawn->GeneratedClass, GetActorLocation(), GetActorRotation(), spawnParams);
            world->SpawnActor<AABItemSiren>(GetActorLocation(), GetActorRotation());
            ItemWidget->SetVisibility(ESlateVisibility::Hidden);
        }
    }
    bIsHoldOnce = true;
}

void AWMASirenSpawner::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AWMASirenSpawner, CollisionBox);
    DOREPLIFETIME(AWMASirenSpawner, bIsVisible);
}

void AWMASirenSpawner::ServerRPCSpawn_Implementation()
{
    MulticastRPCSpawn();
}

void AWMASirenSpawner::MulticastRPCSpawn_Implementation()
{
    UWorld* world = GetWorld();

    FName path = TEXT("/Script/Engine.Blueprint'/Game/Blueprint/BP_ItemSiren.BP_ItemSiren'");
    UBlueprint* ObjectToSpawn = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), NULL, *path.ToString()));
    FActorSpawnParameters spawnParams;
    world->SpawnActor<AActor>(ObjectToSpawn->GeneratedClass, GetActorLocation(), GetActorRotation(), spawnParams);
    ItemWidget->SetVisibility(ESlateVisibility::Hidden);
}

//void AWMASirenSpawner::ServerRPCOverlap_Implementation(AActor* OtherActor)
//{
//    MulticastRPCOverlap(OtherActor);
//}
//
//void AWMASirenSpawner::MulticastRPCOverlap_Implementation(AActor* OtherActor)
//{
//    AWMACharacterPlayer* player = Cast<AWMACharacterPlayer>(OtherActor);
//
//    if (player && player->IsLocallyControlled())
//    {
//        if (ItemWidget)
//        {
//            ItemWidget->SetVisibility(ESlateVisibility::Visible);
//        }
//    }
//    PlayerActor = OtherActor;
//    bIsVisible = true;
//}
//
//void AWMASirenSpawner::ServerRPCOverlapEnd_Implementation(AActor* OtherActor)
//{
//    MulticastRPCOverlapEnd(OtherActor);
//}
//
//void AWMASirenSpawner::MulticastRPCOverlapEnd_Implementation(AActor* OtherActor)
//{
//    AWMACharacterPlayer* player = Cast<AWMACharacterPlayer>(OtherActor);
//
//    if (player && player->IsLocallyControlled())
//    {
//        if (ItemWidget && player->IsLocallyControlled())
//        {
//            ItemWidget->SetVisibility(ESlateVisibility::Hidden);
//            //PlayerActor = NULL;
//        }
//    }
//
//    //
//    bIsVisible = false;
//}
