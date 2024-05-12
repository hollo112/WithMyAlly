// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WMACharacterNonePlayer.h"
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

void AWMACharacterNonePlayer::BeginPlay()
{
	Super::BeginPlay();

	// Stat
	SetName(2);	// CharacterStatTable의 2번째 행, NPC의 스탯으로 바꾼다
	Stat->SetCurrentHp(Stat->GetCharacterStat().MaxHp);
	GetCharacterMovement()->MaxWalkSpeed = Stat->GetCharacterStat().MovementSpeed;

	//GrowlAudioComponent->SetSound(GrowlSound);
	//GrowlAudioComponent->SetVolumeMultiplier(0.2f);
}

AWMACharacterNonePlayer::AWMACharacterNonePlayer()
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

float AWMACharacterNonePlayer::GetPeripheralVisionAngleDegrees() const
{

	return 180.0f;
}

void AWMACharacterNonePlayer::SetDead()
{
	//PlayDeadAnimation();
	//SetActorEnableCollision(false);
	ServerRPCSetDead();
	//Super::SetDead();

	/*FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			Destroy();
		}
	), DeadEventDelayTime, false);*/
}

void AWMACharacterNonePlayer::ServerRPCSetDead_Implementation()
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

void AWMACharacterNonePlayer::MulticastServerRPCSetDead_Implementation()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	PlayDeadAnimation();
}

float AWMACharacterNonePlayer::GetAIPatrolRadius()
{
	return 800.0f;
}

float AWMACharacterNonePlayer::GetAIDetectRange()
{
	return 400.0f;
}

float AWMACharacterNonePlayer::GetAIAttackRange()
{
	return Stat->GetCharacterStat().ShortWPRange;
}

float AWMACharacterNonePlayer::GetAITurnSpeed()
{
	return 2.0f; 
}

float AWMACharacterNonePlayer::SetMovementSpeed()	//좀비 스피드 설정 숫자만 바꿔주면 됨
{
	return GetCharacterMovement()->MaxWalkSpeed  = Stat->GetCharacterStat().MovementSpeed * 7 ;
}

float AWMACharacterNonePlayer::ResetMovementSpeed()
{


	return GetCharacterMovement()->MaxWalkSpeed = Stat->GetCharacterStat().MovementSpeed;
}

void AWMACharacterNonePlayer::SetGrowlSound()
{
	//GrowlAudioComponent->Play();
}

void AWMACharacterNonePlayer::StopGrowlSound()
{
	//GrowlAudioComponent->Stop();
}



void AWMACharacterNonePlayer::SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished)
{
	OnAttackFinished = InOnAttackFinished;
}

void AWMACharacterNonePlayer::AttackByAI()
{
	//MulticastRPCZomAttack();
	if (!bIsAttacking)
	{
		
		ServerRPCAttack();
	}
}

void AWMACharacterNonePlayer::NotifyComboActionEnd()
{
	Super::NotifyComboActionEnd();
	OnAttackFinished.ExecuteIfBound();
}

void AWMACharacterNonePlayer::PlayAttackAnimation()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);
	AnimInstance->Montage_Play(ComboActionMontage);
}

void AWMACharacterNonePlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWMACharacterNonePlayer, bIsAttacking);
}

void AWMACharacterNonePlayer::OnRep_CanCloseAttack()
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

void AWMACharacterNonePlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ensure(ZombieMeshes.Num() > 0);
	int32 RandIndex = FMath::RandRange(0, ZombieMeshes.Num() - 1);
	NPCMeshHandle = UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(ZombieMeshes[RandIndex], FStreamableDelegate::CreateUObject(this, &AWMACharacterNonePlayer::NPCMeshLoadCompleted));
}

void AWMACharacterNonePlayer::NPCMeshLoadCompleted()
{
	ServerRPCSetMesh();
}

void AWMACharacterNonePlayer::MulticastRPCAttack_Implementation()
{
	PlayAttackAnimation();
}

bool AWMACharacterNonePlayer::ServerRPCAttack_Validate()
{
	return true;
}

void AWMACharacterNonePlayer::ServerRPCAttack_Implementation()
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

void AWMACharacterNonePlayer::ServerRPCSetMesh_Implementation()
{
	MulticastRPCSetMesh();
}

void AWMACharacterNonePlayer::MulticastRPCSetMesh_Implementation()
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