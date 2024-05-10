// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/EV_ButtonActor.h"
#include "Components/BoxComponent.h"
#include "Physics/WMACollsion.h"
#include "UI/WMAItemInteractionWidget.h"
#include "Character/WMACharacterPlayer.h"
#include "DoorEVActor.h"
#include "kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AEV_ButtonActor::AEV_ButtonActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(FName("CollisionBox"));
	RootComponent = CollisionBox;
	CollisionBox->SetCollisionProfileName(CPROFILE_WMATRIGGER);
	CollisionBox->SetBoxExtent(FVector(110.0f, 100.0f, 110.0f));

	Button = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button"));
	Button->SetupAttachment(CollisionBox);

	//Widget
	static ConstructorHelpers::FClassFinder<UUserWidget>InputE(TEXT("/Game/UI/WBP_EVInteraction.WBP_EVInteraction_C"));
	if (InputE.Succeeded())
	{
		UE_LOG(LogTemp, Log, TEXT("Createwidget"));
		InteractionButtonWidgetClass = InputE.Class;
	}
}

// Called when the game starts or when spawned
void AEV_ButtonActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (InteractionButtonWidgetClass)
	{
		ButtonWidget = CreateWidget<UUserWidget>(GetWorld(), InteractionButtonWidgetClass);

		if (ButtonWidget)
		{
			ButtonWidget->AddToViewport();
		}
	}

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADoorEVActor::StaticClass(), EVDoors);

	//Timeline
	Timeline.SetTimelineLength(1.0f);

	if (CurveFloat)			// Timeline에 OpenDoor 함수를 바인딩
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindDynamic(this, &AEV_ButtonActor::OpenDoor);
		Timeline.AddInterpFloat(CurveFloat, TimelineProgress);
	}
}

void AEV_ButtonActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AEV_ButtonActor::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AEV_ButtonActor::OnOverlapEnd);
}

// Called every frame
void AEV_ButtonActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timeline.TickTimeline(DeltaTime);
}

void AEV_ButtonActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	AWMACharacterPlayer* player = Cast<AWMACharacterPlayer>(OtherActor);
	if (player && player->IsLocallyControlled() && !bIsOpened)
	{
		if (ButtonWidget)
		{
			ButtonWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void AEV_ButtonActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AWMACharacterPlayer* player = Cast<AWMACharacterPlayer>(OtherActor);

	if (player && player->IsLocallyControlled())
	{
		if (ButtonWidget && player->IsLocallyControlled())
		{
			ButtonWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void AEV_ButtonActor::OpenDoor(float Alpha)
{
	float tmp = FMathf::Lerp(0.0f, 70.0f, Alpha);

	for (auto& EV : EVDoors)
	{
		UStaticMeshComponent* DoorMesh = EV->FindComponentByClass<UStaticMeshComponent>();
		DoorMesh->SetRelativeLocation(FVector(tmp, 0.0f, 0.0f));
	}
}

void AEV_ButtonActor::OnInteract()
{
	if (ButtonWidget->IsVisible())
	{
		ButtonWidget->SetVisibility(ESlateVisibility::Hidden);
		bIsOpened = true;
		Timeline.Play();
	}
}

