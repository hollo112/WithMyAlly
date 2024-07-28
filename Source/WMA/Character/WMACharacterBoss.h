// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundAttenuation.h"
#include "Character/WMACharacterBase.h"
#include "Interface/WMACharacterAIInterface.h"
#include "Interface/WMAAnimationJumpCheckInterface.h"
#include "WMACharacterBoss.generated.h"

/**
 * 
 */
UCLASS(config = WMA)
class WMA_API AWMACharacterBoss : public AWMACharacterBase , public IWMACharacterAIInterface, public IWMAAnimationJumpCheckInterface
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	AWMACharacterBoss();

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
	virtual void BossJumpCheck() override;

	TObjectPtr<class UAnimMontage> JumpAttackMontage;

	FAICharacterAttackFinished OnAttackFinished;

	virtual void NotifyComboActionEnd() override;

	// Actor Replication
	void PlayAttackAnimation();
	void PlayJumpAttackAnimation();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRPCAttack(bool isJumpAttack);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCAttack(bool isJumpAttack);

	UPROPERTY(ReplicatedUsing = OnRep_CanCloseAttack)
	uint8 bIsAttacking : 1;

	UPROPERTY(ReplicatedUsing = OnRep_CanCloseAttack)
	uint8 bIsJumpAttacking : 1;

	UFUNCTION()
	void OnRep_CanCloseAttack();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRPCGunDamaged();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCGunDamaged();

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

	virtual void PlayAttackedAnimation();

	UPROPERTY(ReplicatedUsing = OnRep_GunShoot)
	uint8 bIsDamaging : 1;

	UFUNCTION()
	void OnRep_GunShoot();

public:
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void GunAttackHitCheck();

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
	FVector PlayerLoc;
	void SetPlayerLoc(FVector Loc);
	void JumpAttack();
};
