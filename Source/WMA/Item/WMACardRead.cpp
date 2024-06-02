// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/WMACardRead.h"
#include "Components/BoxComponent.h"
#include "Physics/WMACollsion.h"
#include "UI/WMAItemInteractionWidget.h"
#include "Character/WMACharacterPlayer.h"
#include "kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "WMACardGate.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AWMACardRead::AWMACardRead()
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
void AWMACardRead::BeginPlay()
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

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWMACardGate::StaticClass(), EVDoors);

	//Timeline
	Timeline.SetTimelineLength(1.0f);

	if (CurveFloat)			// Timeline에 OpenDoor 함수를 바인딩
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindDynamic(this, &AWMACardRead::OpenDoor);
		Timeline.AddInterpFloat(CurveFloat, TimelineProgress);
	}
}

void AWMACardRead::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AWMACardRead::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AWMACardRead::OnOverlapEnd);
}

// Called every frame
void AWMACardRead::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timeline.TickTimeline(DeltaTime);
}

void AWMACardRead::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
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

void AWMACardRead::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
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

void AWMACardRead::OpenDoor(float Alpha)
{
	float tmp = FMathf::Lerp(0.0f, 70.0f, Alpha);

	for (auto& EV : EVDoors)
	{
		UStaticMeshComponent* DoorMesh = EV->FindComponentByClass<UStaticMeshComponent>();
		DoorMesh->SetRelativeLocation(FVector(tmp, 0.0f, 0.0f));
	}
}

void AWMACardRead::OnInteract()
{
	if (ButtonWidget->IsVisible())
	{
		ButtonWidget->SetVisibility(ESlateVisibility::Hidden);
		bIsOpened = true;
		Timeline.Play();
	}
}
