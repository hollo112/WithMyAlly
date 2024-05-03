// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/WMACharacterBase.h"
#include "Interface/WMACharacterAIInterface.h"
#include "WMACharacterNonePlayer.generated.h"

/**
 * 
 */
UCLASS()
class WMA_API AWMACharacterNonePlayer : public AWMACharacterBase, public IWMACharacterAIInterface
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	AWMACharacterNonePlayer();

protected:
	void SetDead() override;
	float DeadEventDelayTime = 5.0f;	// 몇초뒤에 사라지게 하기위한 변수

	// AI Section
protected:
	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAITurnSpeed() override;

	virtual void SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished) override;
	virtual void AttackByAI() override;

	FAICharacterAttackFinished OnAttackFinished;

	virtual void NotifyComboActionEnd() override;

	// Actor Replication
	void PlayAttackAnimation();

	UFUNCTION(Client, Unreliable)
	void MulticastRPCZomAttack();
};
