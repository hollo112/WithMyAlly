// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/WMAAnimationCloseAttackInterface.h"
#include "WMACharacterBase.generated.h"

UCLASS()
class WMA_API AWMACharacterBase : public ACharacter, public IWMAAnimationCloseAttackInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWMACharacterBase();
//
//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;
//
//	// Called to bind functionality to input
//	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// 근접 공격 Close Attack Hit Section
protected:
	virtual void CloseAttackHitCheck() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

// 죽는 모션 Dead Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAnimMontage> DeadMontage;

	virtual void SetDead();
	void PlayDeadAnimation();
};
