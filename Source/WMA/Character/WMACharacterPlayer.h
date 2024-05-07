// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/WMACharacterBase.h"
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
	virtual void PossessedBy(AController* NewController) override;			// 컨트롤러 Owner 설정. 클라에서는 일어나지 않음
	virtual void OnRep_Owner() override;									// 클라에서 Owner의 값이 변경되면 실행(클라에서 실행)
	virtual void PostNetInit() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Character Control Section
protected:
	void SetCharacterControl();
	virtual void SetCharacterControlData(const class UWMACharacterControlData* CharacterControlData) override;

	//카메라 관련 Camera
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))	//Meta : private 오브젝트 객체를 블루프린트에서 접근 가능
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;

	//입력 관련 Input
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

	void StartAttacked1();
	void StopAttacked1();
	void StartAttacked2();
	void StopAttacked2();
	void StartAttacked3();
	void StopAttacked3();

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void Attack();
	void PlayCloseAttackAnimation();
	virtual void CloseAttackHitCheck() override;
	void AttackHitConfirm(AActor* HitActor);
	void DrawDebugAttackRange(const FColor& DrawColor, FVector TraceStart, FVector TraceEnd, FVector Forward);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRPCCloseAttack(float AttackStartTime);

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastRPCCloseAttack();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRPCNotifyHit(const FHitResult& HitResult, float HitCheckTime);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRPCNotifyMiss(FVector_NetQuantize TraceStart, FVector_NetQuantize TraceEnd, FVector_NetQuantizeNormal TraceDir, float HitCheckTime);		//FVector용량 크기때문에 NetQuantize로 변경

	UPROPERTY(ReplicatedUsing = OnRep_CanCloseAttack)
	uint8 bCanAttack : 1;

	UFUNCTION()
	void OnRep_CanCloseAttack();

	float CloseAttackTime = 1.27f;					// 공격 끝나는 시간
	float LastCloseAttackStartTime = 0.0f;
	float CloseAttackTimeDifference = 0.0f;			// 서버와 클라의 시간 차이
	float AcceptCheckDistance = 300.0f;				// 공격액터와 피격액터 사이가 3미터 이내면 공격 성공으로 인식
	float AcceptMinCheckTime = 0.15f;

	// 무기 교체
protected:
	void ChangeWeapon_Short();

	void ChangeWeapon_Disposable();

	void ChangeWeapon_Long();

	//Character Mesh
	UPROPERTY(config)
	TArray<FSoftObjectPath> PlayerMeshes;

	void UpdateMeshesFromPlayerState();

	virtual void OnRep_PlayerState();

	//Character AnimInstace
	void UpdateAnimInstance();

public:
	UPROPERTY()
	TObjectPtr<class AActor>MyBat;
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

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UStaticMeshComponent> Hair;
};
