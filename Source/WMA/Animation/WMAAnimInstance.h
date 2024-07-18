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
	uint8 bIsHoldingRifle : 1;												// 총 들고있는지 확인

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	uint8 bIsHoldingFIreExt : 1;												// 총 들고있는지 확인

protected:
	virtual void NativeInitializeAnimation() override;					//처음한번

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;	//프레임마다

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class ACharacter> Owner;									// 캐릭터 정보 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<AWMACharacterPlayer> Player;									// 캐릭터 정보 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class UCharacterMovementComponent> Movement;				// 캐릭터 무브먼트

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	FVector Velocity;													// 캐릭터의 속도 보관

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float GroundSpeed;													// 땅에서의 속도 보관

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)	
	uint8 bIsIdle : 1;													// boolean, idle 상태인지 확인

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float MovingThreshould;												// 움직이고 있는지 쉬고 있는지 확인

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsFalling : 1;												// 떨어지고 있는지 확인

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsJumping : 1;												// 점프하고 있는지 확인

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character)
	uint8 bIsCrouching : 1;												// 앉아있는지 확인

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float JumpingThreshould;											// 점프하고 있는지 확인
};
