// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/WMAEnvQueryContext.h"
#include "Animation/WMAAnimInstance.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/Character.h"
#include "Character/WMACharacterPlayer.h"
#include "Character/WMACharacterNonePlayer.h"
#include <EnvironmentQuery/Items/EnvQueryItemType_Actor.h>

UWMAEnvQueryContext::UWMAEnvQueryContext()
{


}

void UWMAEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);


	ProvideSingleActor(ContextData);

	ProvideActorsSet(ContextData);

}

void UWMAEnvQueryContext::ProvideSingleActor(FEnvQueryContextData& ContextData) const
{
	AActor* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (PlayerCharacter)
	{
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, PlayerCharacter);
	}

}

void UWMAEnvQueryContext::ProvideActorsSet(FEnvQueryContextData& ContextData) const
{
	TArray<AActor*> ActorsOfClass;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWMACharacterPlayer::StaticClass(), ActorsOfClass);

	UEnvQueryItemType_Actor::SetContextHelper(ContextData, ActorsOfClass);
}



