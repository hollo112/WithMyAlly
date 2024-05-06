// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WMACharacterNonePlayer.h"
#include "AI/WMAAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CharacterStat/WMACharacterStatComponent.h"

void AWMACharacterNonePlayer::BeginPlay()
{
	Super::BeginPlay();

	// Stat
	SetName(2);	// CharacterStatTable의 2번째 행, NPC의 스탯으로 바꾼다
	Stat->SetCurrentHp(Stat->GetCharacterStat().MaxHp);
	GetCharacterMovement()->MaxWalkSpeed = Stat->GetCharacterStat().MovementSpeed;
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

float AWMACharacterNonePlayer::SetMovementSpeed()	//좀비 스피드 설정 숫자만 바꿔주면 됨
{
	return GetCharacterMovement()->MaxWalkSpeed  = Stat->GetCharacterStat().MovementSpeed * 7 ;
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