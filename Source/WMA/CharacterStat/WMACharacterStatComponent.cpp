// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStat/WMACharacterStatComponent.h"
#include "GameData/WMAGameSingleton.h"
#include "Net/UnrealNetwork.h"
#include "WMA.h"

// Sets default values for this component's properties
UWMACharacterStatComponent::UWMACharacterStatComponent()
{
	CurrentName = 1;

	AttackRadius = 50.0f;

	SetIsReplicated(true);							// 이 액터 컴포넌트는 네트워크로 리플리케이션 될 준비가 되어있음
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

	if (CurrentHp <= KINDA_SMALL_NUMBER)	// 죽었을 때
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

void UWMACharacterStatComponent::ReadyForReplication()
{
	Super::ReadyForReplication();
}

void UWMACharacterStatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UWMACharacterStatComponent, CurrentHp);
}

void UWMACharacterStatComponent::OnRep_CurrentHp()
{
	OnHpChanged.Broadcast(CurrentHp);
	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		OnHpZero.Broadcast();
	}
}

