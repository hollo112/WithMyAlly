// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/WMACharacterStatComponent.h"
#include "GameData/WMAGameSingleton.h"

// Sets default values for this component's properties
UWMACharacterStatComponent::UWMACharacterStatComponent()
{
	CurrentName = 1;

	AttackRadius = 50.0f;
}


// Called when the game starts
void UWMACharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetNameStat(CurrentName);
	SetHp(CharacterStat.MaxHp);
}

void UWMACharacterStatComponent::SetNameStat(int32 InNewName)
{
	CurrentName = FMath::Clamp(InNewName, 1, UWMAGameSingleton::Get().CharacterMaxLevel);
	CharacterStat = UWMAGameSingleton::Get().GetCharacterStat(CurrentName);
	check(CharacterStat.MaxHp > 0.0f);
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
	CurrentHp = FMath::Clamp<float>(NewHp, 0.0f, CharacterStat.MaxHp);

	OnHpChanged.Broadcast(CurrentHp);
}

