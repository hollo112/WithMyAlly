// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WMACharacterNonePlayer.h"
#include "AI/WMAAIController.h"
#include "Kismet/GameplayStatics.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CharacterStat/WMACharacterStatComponent.h"

void AWMACharacterNonePlayer::BeginPlay()
{
	Super::BeginPlay();

	// Stat
	SetName(2);	// CharacterStatTable�� 2��° ��, NPC�� �������� �ٲ۴�
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

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeadMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/Animation/AM_Dead.AM_Dead'"));
	if (DeadMontageRef.Object)
	{
		DeadMontage = DeadMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ComboActionMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/MyCharacters/Zombie/Animation/AM_ZomAttack.AM_ZomAttack'"));
	if (ComboActionMontageRef.Object)
	{
		ComboActionMontage = ComboActionMontageRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UEnvQuery> EQSQuery(TEXT("EnvQuery'/Game/AI/EQS_FindPlayer.EQS_FindPlayer'"));
	if (EQSQuery.Succeeded())
	{
		MyEQSTemplate = EQSQuery.Object;
	}
}

float AWMACharacterNonePlayer::GetPeripheralVisionAngleDegrees() const
{

	return 180.0f;
}

void AWMACharacterNonePlayer::SetDead()
{
	Super::SetDead();

	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda(
		[&]()
		{
			Destroy();
		}
	), DeadEventDelayTime, false);
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

float AWMACharacterNonePlayer::SetMovementSpeed()	//���� ���ǵ� ���� ���ڸ� �ٲ��ָ� ��
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
	ProcessComboCommand();
	//MulticastRPCZomAttack();
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



void AWMACharacterNonePlayer::MulticastRPCZomAttack_Implementation()
{
	PlayAttackAnimation();
}