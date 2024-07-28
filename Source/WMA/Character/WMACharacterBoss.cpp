// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WMACharacterBoss.h"
#include "WMACharacterBoss.h"
#include "AI/WMABossAIController.h"
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
#include "GameFramework/ProjectileMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include <AI/WMAAI.h>

void AWMACharacterBoss::BeginPlay()
{
	Super::BeginPlay();

	SetName(2);	// CharacterStatTable의 2번째 행, NPC의 스탯으로 바꾼다
	Stat->SetCurrentHp(100.0f);
	GetCharacterMovement()->MaxWalkSpeed = Stat->GetCharacterStat().MovementSpeed;
}

AWMACharacterBoss::AWMACharacterBoss()
{
	AIControllerClass = AWMABossAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	//mesh & animations
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/MyCharacters/BossZombie/BossZombie.BossZombie'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Game/MyCharacters/BossZombie/Animation/ABP_Boss.ABP_Boss_C"));
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeadMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/MyCharacters/BossZombie/Animation/AM_BossDead.AM_BossDead'"));
	if (DeadMontageRef.Object)
	{
		DeadMontage = DeadMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboActionMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/MyCharacters/BossZombie/Animation/AM_BossAttack.AM_BossAttack'"));
	if (ComboActionMontageRef.Object)
	{
		ComboActionMontage = ComboActionMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> JumpAttackMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/MyCharacters/BossZombie/Animation/AM_JumpAttack.AM_JumpAttack'"));
	if (JumpAttackMontageRef.Object)
	{
		JumpAttackMontage = JumpAttackMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackedMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/MyCharacters/Zombie/Animation/AM_Zombie_Reaction_Hit_Montage.AM_Zombie_Reaction_Hit_Montage'"));
	if (AttackedMontageRef.Object) {
		AttackedMontage = AttackedMontageRef.Object;
	}

	GetCharacterMovement()->BrakingDecelerationFalling = 0.0f;
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

	AWMABossAIController* AIController = Cast<AWMABossAIController>(GetController());
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
	), 4.5f, false);
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
	return 2000.0f;
}

float AWMACharacterBoss::GetAIAttackRange()
{
	return 200.0f;
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

		ServerRPCAttack(false);
	}
}

void AWMACharacterBoss::BossJumpCheck()
{
	FVector OutVelocity = FVector::ZeroVector;
	FVector EndPos = FVector(PlayerLoc.X, PlayerLoc.Y, PlayerLoc.Z + 100.0f);
	UGameplayStatics::SuggestProjectileVelocity_CustomArc(this, OutVelocity, GetActorLocation(), EndPos);
	UE_LOG(LogTemp, Log, TEXT("Character Location :: %s"), *GetActorLocation().ToString());
	UE_LOG(LogTemp, Log, TEXT("Player Location :: %s"), *EndPos.ToString());
	UE_LOG(LogTemp, Log, TEXT("OutVelocity Location :: %s"), *OutVelocity.ToString());
	LaunchCharacter(OutVelocity, false, true);
	UE_LOG(LogTemp, Log, TEXT("Boss Jump3"));

	FTimerHandle AttackTimerHandle;
	float AttackTime = 2.0f;

	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, FTimerDelegate::CreateLambda([&]
		{
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		}
	), AttackTime, false);
	
}

void AWMACharacterBoss::JumpAttack()
{
	if (!bIsAttacking)
	{
		UE_LOG(LogTemp, Log, TEXT("Boss Jump1"));
		ServerRPCAttack(true);
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

void AWMACharacterBoss::PlayJumpAttackAnimation()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);
	AnimInstance->Montage_Play(JumpAttackMontage);
}

void AWMACharacterBoss::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWMACharacterBoss, bIsAttacking);
	DOREPLIFETIME(AWMACharacterBoss, bIsJumpAttacking);
}

bool AWMACharacterBoss::ServerRPCAttack_Validate(bool isJumpAttack)
{
	return true;
}

void AWMACharacterBoss::ServerRPCAttack_Implementation(bool isJumpAttack)
{
	//ProcessComboCommand();

	bIsAttacking = true;
	if (!isJumpAttack)
	{		
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	}
	else
	{
		bIsJumpAttacking = true;
	}
	OnRep_CanCloseAttack();

	FTimerHandle AttackTimerHandle;
	float AttackTime = 4.6;

	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, FTimerDelegate::CreateLambda([&]
		{
			bIsAttacking = false;
			bIsJumpAttacking = false;
			OnRep_CanCloseAttack();
		}
	), AttackTime, false);

	if (isJumpAttack)
	{
		PlayJumpAttackAnimation();
	}
	else
	{
		PlayAttackAnimation();
	}
	MulticastRPCAttack(isJumpAttack);
}

void AWMACharacterBoss::MulticastRPCAttack_Implementation(bool isJumpAttack)
{
	if (isJumpAttack)
	{
		PlayJumpAttackAnimation();
	}
	else
	{
		PlayAttackAnimation();
	}
}

void AWMACharacterBoss::OnRep_CanCloseAttack()
{
	if (bIsAttacking && !bIsJumpAttacking)
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	}
	else
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	}
}

bool AWMACharacterBoss::ServerRPCGunDamaged_Validate()
{
	return true;
}

void AWMACharacterBoss::ServerRPCGunDamaged_Implementation()
{
	FDamageEvent DamageEvent;
	TakeDamage(1.f, DamageEvent, GetController(), this);

	MulticastRPCGunDamaged();
}

void AWMACharacterBoss::MulticastRPCGunDamaged_Implementation()
{

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

void AWMACharacterBoss::PlayAttackedAnimation()
{
	if (Stat->GetCurrentHp() > 0)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		AnimInstance->StopAllMontages(0.0f);

		AnimInstance->Montage_Play(AttackedMontage, 1.0f);
	}
}

void AWMACharacterBoss::GunAttackHitCheck()
{
	ServerRPCGunDamaged();
}

void AWMACharacterBoss::SetPlayerLoc(FVector Loc)
{
	PlayerLoc = Loc;
}
