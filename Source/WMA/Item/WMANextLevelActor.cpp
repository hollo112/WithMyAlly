// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/WMANextLevelActor.h"
#include "Components/BoxComponent.h"
#include "Physics/WMACollsion.h"
#include "Engine/Engine.h"
#include "UI/WMAItemInteractionWidget.h"
#include "Game/WMAGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AWMANextLevelActor::AWMANextLevelActor()
{
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(FName("CollisionBox"));

    CollisionBox->SetCollisionProfileName(CPROFILE_WMATRIGGER);
    CollisionBox->SetBoxExtent(FVector(110.0f, 100.0f, 110.0f));
   
    CollisionBox->SetupAttachment(RootComponent);
   
    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AWMANextLevelActor::OnOverlapBegin);
    CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AWMANextLevelActor::OnOverlapEnd);
    //Widget
    static ConstructorHelpers::FClassFinder<UUserWidget>LoadingUI(TEXT("/Game/UI/WB_Loading.WB_Loading_C"));
    if (LoadingUI.Succeeded())
    {
        LoadingWidget = LoadingUI.Class;
    }
}

// Called when the game starts or when spawned
void AWMANextLevelActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWMANextLevelActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
    ++count;
    if (count == 2)
    {
        if (LoadingWidget)
        {
            Widget = CreateWidget<UUserWidget>(GetWorld(), LoadingWidget);

            if (LoadingWidget)
            {
                Widget->AddToViewport();
            }
        }
        AWMAGameModeBase* GameMode = Cast<AWMAGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
        if (GameMode)
        {
            UE_LOG(LogTemp, Log, TEXT("Log Travel"));
            //GameMode->bUseSeamlessTravel = true;
            GameMode->TravelNewMap();
        }
    }
}

void AWMANextLevelActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    --count;
}

void AWMANextLevelActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
