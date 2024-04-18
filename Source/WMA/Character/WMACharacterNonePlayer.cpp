// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/WMACharacterNonePlayer.h"
#include "AI/WMAAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CharacterStat/WMACharacterStatComponent.h"

void AWMACharacterNonePlayer::BeginPlay()
{
	Super::BeginPlay();

// Stat
	SetName(2);											// CharacterStatTable의 2번째 행, NPC의 스탯으로 바꾼다
	Stat->SetCurrentHp(Stat->GetCharacterStat().MaxHp);
	GetCharacterMovement()->MaxWalkSpeed = Stat->GetCharacterStat().MovementSpeed; 
}

AWMACharacterNonePlayer::AWMACharacterNonePlayer()
{
	AIControllerClass = AWMAAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
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

void AWMACharacterNonePlayer::SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished)
{
	OnAttackFinished = InOnAttackFinished;
}

void AWMACharacterNonePlayer::AttackByAI()
{
	ProcessComboCommand();
	PlayCloseAttackAnimation();
}

void AWMACharacterNonePlayer::NotifyComboActionEnd()
{
	Super::NotifyComboActionEnd();
	OnAttackFinished.ExecuteIfBound();
}

void AWMACharacterNonePlayer::PlayCloseAttackAnimation()
{
	if (!HasAuthority())
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		AnimInstance->StopAllMontages(0.0f);
		AnimInstance->Montage_Play(ComboActionMontage);
	}
}
