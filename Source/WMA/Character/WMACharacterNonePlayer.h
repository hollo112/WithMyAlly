// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundAttenuation.h"
#include "Character/WMACharacterBase.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "AI/BTService_Detect.h"
#include "Interface/WMACharacterAIInterface.h"
#include "WMACharacterNonePlayer.generated.h"

/**
 * 
 */
UCLASS(config = WMA)
class WMA_API AWMACharacterNonePlayer : public AWMACharacterBase, public IWMACharacterAIInterface
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	AWMACharacterNonePlayer();

	virtual float GetPeripheralVisionAngleDegrees() const override;

protected:
	void SetDead() override;
	UFUNCTION(Server, Reliable)
	void ServerRPCSetDead();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastServerRPCSetDead();

	float DeadEventDelayTime = 5.0f;	// 몇초뒤에 사라지게 하기위한 변수

	// AI Section
protected:
	virtual float GetAIPatrolRadius() override;
	virtual float GetAIDetectRange() override;
	virtual float GetAIAttackRange() override;
	virtual float GetAITurnSpeed() override;
	virtual float SetMovementSpeed() override;
	virtual float ResetMovementSpeed() override;
	virtual void SetGrowlSound() override;
	virtual void StopGrowlSound() override;

	virtual void SetAIAttackDelegate(const FAICharacterAttackFinished& InOnAttackFinished) override;
	virtual void AttackByAI() override;

	FAICharacterAttackFinished OnAttackFinished;

	virtual void NotifyComboActionEnd() override;

	// Actor Replication
	void PlayAttackAnimation();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRPCAttack();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCAttack();

	UPROPERTY(ReplicatedUsing = OnRep_CanCloseAttack)
	uint8 bIsAttacking : 1;

	UFUNCTION()
	void OnRep_CanCloseAttack();

	//Zombie Mesh
	virtual void PostInitializeComponents() override;
	void NPCMeshLoadCompleted();

	UPROPERTY(config)
	TArray<FSoftObjectPath> ZombieMeshes;

	TSharedPtr<FStreamableHandle> NPCMeshHandle;

	UFUNCTION(Server, Reliable)
	void ServerRPCSetMesh();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCSetMesh();

public:
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void GunAttackHitCheck();
};
