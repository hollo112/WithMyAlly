// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WMACharacterBoss.h"
#include "WMACharacterBoss.h"
#include "AI/WMAAIController.h"
#include "Kismet/GameplayStatics.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CharacterStat/WMACharacterStatComponent.h"
#include "WMACharacterPlayer.h"
#include "GameFramework/GameStateBase.h"
#include "EngineUtils.h"
#include "Engine/AssetManager.h"
#include "Net/UnrealNetwork.h"
#include "Engine/DamageEvents.h"


void AWMACharacterBoss::BeginPlay()
{
	Super::BeginPlay();

	SetName(2);	// CharacterStatTable의 2번째 행, NPC의 스탯으로 바꾼다
	Stat->SetCurrentHp(Stat->GetCharacterStat().MaxHp);
	GetCharacterMovement()->MaxWalkSpeed = Stat->GetCharacterStat().MovementSpeed;
}

AWMACharacterBoss::AWMACharacterBoss()
{
	AIControllerClass = AWMAAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	//mesh & animations
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Game/MyCharacters/Zombie/Zombie_Idle.Zombie_Idle"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/MyCharacters/Zombie/Animation/ABP_Zombie.ABP_Zombie_C"));
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeadMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/MyCharacters/Zombie/Animation/AM_ZomDead.AM_ZomDead'"));
	if (DeadMontageRef.Object)
	{
		DeadMontage = DeadMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboActionMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/MyCharacters/Zombie/Animation/AM_ZomAttack.AM_ZomAttack'"));
	if (ComboActionMontageRef.Object)
	{
		ComboActionMontage = ComboActionMontageRef.Object;
	}

}

float AWMACharacterBoss::GetPeripheralVisionAngleDegrees() const
{
	return 180.0f;
}

void AWMACharacterBoss::SetDead()
{
	ServerRPCSetDead();

}

void AWMACharacterBoss::ServerRPCSetDead_Implementation()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);	// 움직이지 못하게 하기
	PlayDeadAnimation();
	SetActorEnableCollision(false);

	MulticastServerRPCSetDead();

	AWMAAIController* AIController = Cast<AWMAAIController>(GetController());
	if (AIController)
	{
		AIController->StopAI();
	}

	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			Destroy();
		}
	), DeadEventDelayTime, false);
}

void AWMACharacterBoss::MulticastServerRPCSetDead_Implementation()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	PlayDeadAnimation();
}

float AWMACharacterBoss::GetAIPatrolRadius()
{
	return 800.0f;
}

float AWMACharacterBoss::GetAIDetectRange()
{
	return 1200.0f;
}

float AWMACharacterBoss::GetAIAttackRange()
{
	return Stat->GetCharacterStat().ShortWPRange;
}

float AWMACharacterBoss::GetAITurnSpeed()
{
	return 2.0f;
}

float AWMACharacterBoss::SetMovementSpeed()
{
	return GetCharacterMovement()->MaxWalkSpeed = Stat->GetCharacterStat().MovementSpeed * 7;
}

float AWMACharacterBoss::ResetMovementSpeed()
{
	return GetCharacterMovement()->MaxWalkSpeed = Stat->GetCharacterStat().MovementSpeed;
}

void AWMACharacterBoss::SetGrowlSound()
{

}

void AWMACharacterBoss::StopGrowlSound()
{

}

void AWMACharacterBoss::SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished)
{
	OnAttackFinished = InOnAttackFinished;
}

void AWMACharacterBoss::AttackByAI()
{
	if (!bIsAttacking)
	{

		ServerRPCAttack();
	}
}

void AWMACharacterBoss::NotifyComboActionEnd()
{
	Super::NotifyComboActionEnd();
	OnAttackFinished.ExecuteIfBound();
}

void AWMACharacterBoss::PlayAttackAnimation()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);
	AnimInstance->Montage_Play(ComboActionMontage);
}

void AWMACharacterBoss::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWMACharacterBoss, bIsAttacking);
}

bool AWMACharacterBoss::ServerRPCAttack_Validate()
{
	return true;
}

void AWMACharacterBoss::ServerRPCAttack_Implementation()
{
	//ProcessComboCommand();

	bIsAttacking = true;
	OnRep_CanCloseAttack();
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

	FTimerHandle AttackTimerHandle;
	float AttackTime = 4.6;

	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, FTimerDelegate::CreateLambda([&]
		{
			bIsAttacking = false;
			OnRep_CanCloseAttack();
		}
	), AttackTime, false);

	PlayAttackAnimation();
	MulticastRPCAttack();
}

void AWMACharacterBoss::MulticastRPCAttack_Implementation()
{
	PlayAttackAnimation();
}

void AWMACharacterBoss::OnRep_CanCloseAttack()
{
	if (bIsAttacking)
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	}
	else
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}
}

void AWMACharacterBoss::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (ZombieMeshes.Num() > 0)
	{
		int32 RandIndex = FMath::RandRange(0, ZombieMeshes.Num() - 1);
		NPCMeshHandle = UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(ZombieMeshes[RandIndex], FStreamableDelegate::CreateUObject(this, &AWMACharacterBoss::NPCMeshLoadCompleted));
	}
}

void AWMACharacterBoss::NPCMeshLoadCompleted()
{
	ServerRPCSetMesh();
}

void AWMACharacterBoss::ServerRPCSetMesh_Implementation()
{
	MulticastRPCSetMesh();
}

void AWMACharacterBoss::MulticastRPCSetMesh_Implementation()
{
	if (NPCMeshHandle.IsValid())
	{
		USkeletalMesh* NPCMesh = Cast<USkeletalMesh>(NPCMeshHandle->GetLoadedAsset());
		if (NPCMesh)
		{
			GetMesh()->SetSkeletalMesh(NPCMesh);
			GetMesh()->SetHiddenInGame(false);
		}
	}

	NPCMeshHandle->ReleaseHandle();
}

void AWMACharacterBoss::GunAttackHitCheck()
{
}
