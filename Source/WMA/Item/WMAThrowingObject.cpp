// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/WMAThrowingObject.h"
#include "Components/SphereComponent.h"
#include "Physics/WMACollsion.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AWMAThrowingObject::AWMAThrowingObject()
{
    //DefaultScene = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultScene"));
    
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    CollisionSphere->SetCollisionProfileName(CPROFILE_WMATRIGGER);
    CollisionSphere->InitSphereRadius(20.f);
    //CollisionSphere->SetupAttachment(DefaultScene);
    RootComponent = CollisionSphere;
    Mesh->SetupAttachment(CollisionSphere);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxMeshRef1(TEXT("/Script/Engine.StaticMesh'/Game/Item/Samdasoo/samdasoo1.samdasoo1'"));
    if (BoxMeshRef1.Succeeded())
    {
        Mesh->SetStaticMesh(BoxMeshRef1.Object);
    }

    Mesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));
    Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    Mesh->SetIsReplicated(true);

    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    ProjectileMovementComponent->SetUpdatedComponent(CollisionSphere);
    ProjectileMovementComponent->InitialSpeed = 800.0f;
    ProjectileMovementComponent->MaxSpeed = 850.0f;
    ProjectileMovementComponent->bRotationFollowsVelocity = false;
    ProjectileMovementComponent->bShouldBounce = true;
    ProjectileMovementComponent->Bounciness = 0.6f;
}

// Called when the game starts or when spawned
void AWMAThrowingObject::BeginPlay()
{
	Super::BeginPlay();

    CollisionSphere->OnComponentHit.AddDynamic(this, &AWMAThrowingObject::OnHit);
    UE_LOG(LogTemp, Log, TEXT("Character Location :: %s"), *GetActorLocation().ToString());
}

void AWMAThrowingObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AWMAThrowingObject, CollisionSphere);
}

void AWMAThrowingObject::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    if (!isHit)
    {
        isHit = true;
        UE_LOG(LogTemp, Log, TEXT("Log Thorwing Hit"));
        const float SoundStrength = 120.0f;
      
        AISenseHearing->ReportNoiseEvent(this, GetActorLocation(), SoundStrength, this, 300.0f, FName("Throw"));
        UE_LOG(LogTemp, Log, TEXT("Character Location :: %s"), *GetActorLocation().ToString());

        FTimerHandle myTimerHandle;
        GetWorld()->GetTimerManager().SetTimer(myTimerHandle, FTimerDelegate::CreateLambda([&]()
        {
            Destroy();

        }), 5.0f, false);
    }
}


