// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/WMACharacterBase.h"
#include "InputActionValue.h"
#include "WMACharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class WMA_API AWMACharacterPlayer : public AWMACharacterBase
{
	GENERATED_BODY()
	
public:
	AWMACharacterPlayer();

protected:
	virtual void BeginPlay() override;
	virtual void SetDead() override;
	virtual void PossessedBy(AController* NewController) override;			// ��Ʈ�ѷ� Owner ����. Ŭ�󿡼��� �Ͼ�� ����
	virtual void OnRep_Owner() override;									// Ŭ�󿡼� Owner�� ���� ����Ǹ� ����(Ŭ�󿡼� ����)
	virtual void PostNetInit() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// Character Control Section
protected:
	void SetCharacterControl();
	virtual void SetCharacterControlData(const class UWMACharacterControlData* CharacterControlData) override;

//ī�޶� ���� Camera
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))	//Meta : private ������Ʈ ��ü�� �������Ʈ���� ���� ����
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;

//�Է� ���� Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> AttackAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void Attack();
	virtual void CloseAttackHitCheck() override;

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRPCCloseAttack();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCCloseAttack();

	UPROPERTY(ReplicatedUsing = OnRep_CanCloseAttack)
	uint8 bCanAttack : 1;

	UFUNCTION()
	void OnRep_CanCloseAttack();

	float CloseAttackTime = 1.27f;					// ���� ������ �ð�
// ���� ��ü
protected:
	void ChangeWeapon_Short();

	void ChangeWeapon_Disposable();

	void ChangeWeapon_Long();
};
