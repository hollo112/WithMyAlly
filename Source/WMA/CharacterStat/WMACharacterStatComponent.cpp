// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/WMACharacterStatComponent.h"

// Sets default values for this component's properties
UWMACharacterStatComponent::UWMACharacterStatComponent()
{
	MaxHp = 10.0f;
	CurrentHp = MaxHp;
}


// Called when the game starts
void UWMACharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHp(MaxHp);
	
}

float UWMACharacterStatComponent::ApplyDamage(float InDamage)
{
	const float PrevHp = CurrentHp;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0, InDamage);

	SetHp(PrevHp - ActualDamage);

	if (CurrentHp <= KINDA_SMALL_NUMBER)	// Á×¾úÀ» ¶§
	{
		OnHpZero.Broadcast();
	}
	return ActualDamage;
}

void UWMACharacterStatComponent::SetHp(float NewHp)
{
	CurrentHp = FMath::Clamp<float>(NewHp, 0.0f, MaxHp);

	OnHpChanged.Broadcast(CurrentHp);
}

