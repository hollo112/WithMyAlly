// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameData/WMACharacterStat.h"
#include "WMACharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);										// 델리게이트. 죽었을 때 신호
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate, float /*CurrentHp*/);		// 현재 HP

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WMA_API UWMACharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWMACharacterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	FOnHpZeroDelegate OnHpZero;
	FOnHpChangedDelegate OnHpChanged;

	void SetNameStat(int32 InNewName);																// CharacterStatTable의 행값을 받아 스탯 설정
	FORCEINLINE float GetCurrentName() const { return CurrentName; }
	FORCEINLINE float GetCurrentHp() { return CurrentHp; }
	void SetCurrentHp(float InHp) { CurrentHp = InHp; }
	FORCEINLINE FWMACharacterStat GetCharacterStat() const { return CharacterStat; }					// GetTotalStat에서 변경
	FORCEINLINE float GetAttackRadius() { return AttackRadius; }

	float ApplyDamage(float InDamage);

protected:
	void SetHp(float NewHp);

	//UPROPERTY(VisibleInstanceOnly, Category = Stat)
	//float MaxHp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentName;																					// CurrentLevel에서 변경

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	FWMACharacterStat CharacterStat;

	UPROPERTY(VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	float AttackRadius;
};
