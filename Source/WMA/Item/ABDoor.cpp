// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ABDoor.h"
#include "Components/BoxComponent.h"
#include "Physics/WMACollsion.h"
#include "UI/WMAItemInteractionWidget.h"
#include "Character/WMACharacterPlayer.h"
#include "kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AABDoor::AABDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EmptyScene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	EmptyScene->SetupAttachment(RootComponent);

	DoorRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DoorRoot"));
	DoorRoot->SetupAttachment(EmptyScene);

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Doorhand1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Doorhand1"));
	Doorhand2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Doorhand2"));
	DoorM1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorM1"));
	DoorM2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorM2"));
	DoorM3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorM3"));
	Doorname = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Doorname"));

	Door->SetupAttachment(DoorRoot);

	Doorhand1->SetupAttachment(Door);
	Doorhand2->SetupAttachment(Doorhand1);

	DoorM1->SetupAttachment(Door);
	DoorM2->SetupAttachment(Door);
	DoorM3->SetupAttachment(Door);
	Doorname->SetupAttachment(Door);


	Door_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door_2"));
	Doorhand1_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Doorhand1_2"));
	Doorhand2_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Doorhand2_2"));
	DoorM1_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorM1_2"));
	DoorM2_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorM2_2"));
	DoorM3_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorM3_2"));
	Doorname_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Doorname_2"));

	Door_2->SetupAttachment(DoorRoot);

	Doorhand1_2->SetupAttachment(Door_2);
	Doorhand2_2->SetupAttachment(Doorhand1_2);

	DoorM1_2->SetupAttachment(Door_2);
	DoorM2_2->SetupAttachment(Door_2);
	DoorM3_2->SetupAttachment(Door_2);
	Doorname_2->SetupAttachment(Door_2);


	static ConstructorHelpers::FObjectFinder<UStaticMesh>DoorMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Item/Door/Doorfbx_Plane001.Doorfbx_Plane001'"));
	if (DoorMeshRef.Object) {
		Door->SetStaticMesh(DoorMeshRef.Object);
		Door_2->SetStaticMesh(DoorMeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh>Doorhand1MeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Item/Door/Doorfbx_Box001.Doorfbx_Box001'"));
	if (Doorhand1MeshRef.Object) {
		Doorhand1->SetStaticMesh(Doorhand1MeshRef.Object);
		Doorhand1_2->SetStaticMesh(Doorhand1MeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh>Doorhand2MeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Item/Door/Doorfbx_Box002.Doorfbx_Box002'"));
	if (Doorhand2MeshRef.Object) {
		Doorhand2->SetStaticMesh(Doorhand2MeshRef.Object);
		Doorhand2_2->SetStaticMesh(Doorhand2MeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh>DoorM1MeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Item/Door/Doorfbx_Cylinder001.Doorfbx_Cylinder001'"));
	if (DoorM1MeshRef.Object) {
		DoorM1->SetStaticMesh(DoorM1MeshRef.Object);
		DoorM1_2->SetStaticMesh(DoorM1MeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh>DoorM2MeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Item/Door/Doorfbx_Cylinder002.Doorfbx_Cylinder002'"));
	if (DoorM2MeshRef.Object) {
		DoorM2->SetStaticMesh(DoorM2MeshRef.Object);
		DoorM2_2->SetStaticMesh(DoorM2MeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh>DoorM3MeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Item/Door/Doorfbx_Cylinder003.Doorfbx_Cylinder003'"));
	if (DoorM3MeshRef.Object) {
		DoorM3->SetStaticMesh(DoorM3MeshRef.Object);
		DoorM3_2->SetStaticMesh(DoorM3MeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh>DoornameMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/Item/Door/Doorfbx_Plane002.Doorfbx_Plane002'"));
	if (DoornameMeshRef.Object) {
		Doorname->SetStaticMesh(DoornameMeshRef.Object);
		Doorname_2->SetStaticMesh(DoornameMeshRef.Object);
	}

	// Collision
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(FName("CollisionBox"));
	CollisionBox->SetupAttachment(DoorRoot);
	CollisionBox->SetCollisionProfileName(CPROFILE_WMATRIGGER);
	CollisionBox->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	// Widget
	static ConstructorHelpers::FClassFinder<UUserWidget>InputE(TEXT("/Game/UI/WBP_EVInteraction.WBP_EVInteraction_C"));
	if (InputE.Succeeded())
	{
		InteractionButtonWidgetClass = InputE.Class;
	}
}

void AABDoor::BeginPlay()
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

	//Timeline
	Timeline.SetTimelineLength(1.0f);

	if (CurveFloat)			// Timeline에 OpenDoor 함수를 바인딩
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindDynamic(this, &AABDoor::OpenDoor);
		Timeline.AddInterpFloat(CurveFloat, TimelineProgress);
	}

	bIsOpened = false;
}

void AABDoor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AABDoor::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AABDoor::OnOverlapEnd);
}

void AABDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timeline.TickTimeline(DeltaTime);
}

void AABDoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	PlayerActor = OtherActor;
	AWMACharacterPlayer* player = Cast<AWMACharacterPlayer>(OtherActor);
	if (player && player->IsLocallyControlled() && !bIsOpened)
	{
		if (ButtonWidget)
		{
			ButtonWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void AABDoor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PlayerActor = NULL;
	AWMACharacterPlayer* player = Cast<AWMACharacterPlayer>(OtherActor);

	if (player && player->IsLocallyControlled())
	{
		if (ButtonWidget && player->IsLocallyControlled())
		{
			ButtonWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void AABDoor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AABDoor, bIsOpened);
}

void AABDoor::OpenDoor(float Alpha)
{
	UE_LOG(LogTemp, Log, TEXT("Open!"));

	float tmp = FMathf::Lerp(0.0f, 90.0f, Alpha);

	DoorRoot->SetRelativeRotation(FRotator(0.0f, tmp, 0.0f ));
}

void AABDoor::OnInteract()
{
	if (!bIsOpened && PlayerActor && HasAuthority())
	{
		ButtonWidget->SetVisibility(ESlateVisibility::Hidden);
		bIsOpened = true;
		Timeline.Play();
	}
}


