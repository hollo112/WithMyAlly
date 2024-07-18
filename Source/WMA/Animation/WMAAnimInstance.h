// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "WMAAnimInstance.generated.h"

/**
 * 
 */
class AWMACharacterPlayer;

UCLASS()
class WMA_API UWMAAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UWMAAnimInstance();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	uint8 bIsHoldingRifle : 1;												// �� ����ִ��� Ȯ��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	uint8 bIsHoldingFIreExt : 1;												// �� ����ִ��� Ȯ��

protected:
	virtual void NativeInitializeAnimation() override;					//ó���ѹ�

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;	//�����Ӹ���

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class ACharacter> Owner;									// ĳ���� ���� 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<AWMACharacterPlayer> Player;									// ĳ���� ���� 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class UCharacterMovementComponent> Movement;				// ĳ���� �����Ʈ

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	FVector Velocity;													// ĳ������ �ӵ� ����

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float GroundSpeed;													// �������� �ӵ� ����

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)	
	uint8 bIsIdle : 1;													// boolean, idle �������� Ȯ��

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float MovingThreshould;												// �����̰� �ִ��� ���� �ִ��� Ȯ��

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsFalling : 1;												// �������� �ִ��� Ȯ��

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsJumping : 1;												// �����ϰ� �ִ��� Ȯ��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	uint8 bIsCrouching : 1;												// �ɾ��ִ��� Ȯ��

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float JumpingThreshould;											// �����ϰ� �ִ��� Ȯ��
};
