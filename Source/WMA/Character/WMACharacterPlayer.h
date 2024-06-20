// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/WMACharacterBase.h"
#include "Perception/AISense_Hearing.h"
#include "InputActionValue.h"
#include "WMACharacterPlayer.generated.h"

/**
 *
 */
UCLASS(config = WMA)
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

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	bool bIsESCOpened = false;
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ESCAction;

	void ESCInput();
	TSubclassOf<UUserWidget> ESCMenuWidgetClass;
	UUserWidget* ESCWidget;
	UFUNCTION(Server, Reliable)
	void ServerESC();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastESC();

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void Attack();
	void PlayCloseAttackAnimation();
	
	void DrawDebugAttackRange(const FColor& DrawColor, FVector TraceStart, FVector TraceEnd, FVector Forward);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRPCCloseAttack(float AttackStartTime);

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastRPCCloseAttack();

	UPROPERTY(ReplicatedUsing = OnRep_CanCloseAttack)
	uint8 bCanAttack : 1;

	UFUNCTION()
	void OnRep_CanCloseAttack();

	float CloseAttackTime = 2.2f;					// ���� ������ �ð�
	float LastCloseAttackStartTime = 0.0f;
	float CloseAttackTimeDifference = 0.0f;			// ������ Ŭ���� �ð� ����
	float AcceptCheckDistance = 300.0f;				// ���ݾ��Ϳ� �ǰݾ��� ���̰� 3���� �̳��� ���� �������� �ν�
	float AcceptMinCheckTime = 0.15f;

	// ���� ��ü
protected:
	void ChangeWeapon_Short();
	void ChangeWeapon_Disposable();
	void ChangeWeapon_Long();
	UFUNCTION(Server, Reliable)
	void ServerRPCChangeWP(EItemType InItemData);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCChangeWP(EItemType InItemData);

	//Character Mesh
	UPROPERTY(config)
	TArray<FSoftObjectPath> PlayerMeshes;

	virtual void OnRep_PlayerState();

	//Character AnimInstace
	void UpdateAnimInstance();

protected:
	UPROPERTY(VisibleAnywhere, Category = Box)
	TObjectPtr<class UBoxComponent> Trigger;

	// Running
	UFUNCTION(Server, Reliable)
	void ServerSprint(bool isSprinting);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastSprint(bool isSprinting);

	bool bIsHoldingSprintButton;

	void SprintHold();
	void SprintRelease();

	void InteractHold();
	void InteractRelease();

	// Picking
	UFUNCTION(Server, Reliable)
	void ServerRPCPickUp();
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCPickUp();

	UFUNCTION(Server, Reliable)
	void ServerRPCTakeItem(UABItemData* InItemData);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCTakeItem(UABItemData* InItemData);

	virtual void TakeItem(class UABItemData* InItemData) override;

	//�ǰݽ� UI
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UStaticMeshComponent> Hair;

	// AI Hearing
public:
	UAISense_Hearing* AISenseHearing;
protected:
	UFUNCTION(Server, Reliable)
	void ServerRPCMovingSound(FVector ClientLocation, bool bClientHolding);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCMovingSound();

	//Stabbing Montage
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	TObjectPtr<class UAnimMontage> StabbingMontage;
};
