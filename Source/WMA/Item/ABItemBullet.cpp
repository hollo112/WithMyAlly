// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ABItemBullet.h"
#include "Components/StaticMeshComponent.h"
#include "Physics/WMACollsion.h"
#include "Components/SphereComponent.h"
#include "Interface/ABCharacterItemInterface.h"
#include "Interface/ABCharacterItemInterface.h"
#include "Character/WMACharacterNonePlayer.h"
#include "Character/WMACharacterBoss.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AABItemBullet::AABItemBullet()
{
    Mesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh1"));
    Mesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh2"));

    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    CollisionSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    CollisionSphere->InitSphereRadius(4.5f);
    //CollisionSphere->SetupAttachment(DefaultScene);
    RootComponent = CollisionSphere;
    Mesh1->SetupAttachment(CollisionSphere);
    Mesh2->SetupAttachment(Mesh1);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef1(TEXT("/Script/Engine.StaticMesh'/Game/Item/bullet/bullet_Object001.bullet_Object001'"));
    if (MeshRef1.Succeeded())
    {
        Mesh1->SetStaticMesh(MeshRef1.Object);
    }

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef2(TEXT("/Script/Engine.StaticMesh'/Game/Item/bullet/bullet_Cone001.bullet_Cone001'"));
    if (MeshRef2.Succeeded())
    {
        Mesh2->SetStaticMesh(MeshRef2.Object);
    }
    Mesh1->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));

    Mesh1->SetCollisionProfileName(TEXT("NoCollision"));
    Mesh1->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    Mesh1->SetIsReplicated(true);
    Mesh2->SetCollisionProfileName(TEXT("NoCollision"));
    Mesh2->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    Mesh2->SetIsReplicated(true);

    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    ProjectileMovementComponent->SetUpdatedComponent(CollisionSphere);
    ProjectileMovementComponent->InitialSpeed = 1200.0f;
    ProjectileMovementComponent->MaxSpeed = 1500.0f;
    ProjectileMovementComponent->bRotationFollowsVelocity = false;
    ProjectileMovementComponent->bShouldBounce = false;
    ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

    CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AABItemBullet::OnOverlapBegin);
    CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AABItemBullet::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AABItemBullet::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle myTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(myTimerHandle, FTimerDelegate::CreateLambda([&]()
	{
		Destroy();

	}), 4.0f, false);
}

void AABItemBullet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AABItemBullet, CollisionSphere);
}

void AABItemBullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
    if (OtherActor)
    {
        AWMACharacterNonePlayer* NPC = Cast<AWMACharacterNonePlayer>(OtherActor);
        if (HasAuthority() && NPC)
        {
            NPC->GunAttackHitCheck();
            Destroy();
        }

        AWMACharacterBoss* Boss = Cast<AWMACharacterBoss>(OtherActor);
        if (HasAuthority() && Boss)
        {
            Boss->GunAttackHitCheck();
            Destroy();
        }
    }
}

void AABItemBullet::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

