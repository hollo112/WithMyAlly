// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/WMAEnvQueryContext.h"
#include "Animation/WMAAnimInstance.h"


UWMAEnvQueryContext::UWMAEnvQueryContext()
{


}

void UWMAEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	
}

void UWMAEnvQueryContext::ProvideSingleActor(UObject* QuerierObject, AActor* QuerierActor, AActor*& ResultingActor) 
{
	AActor*& RA = ResultingActor;
	if (RA) {
		FVector PlayerLocation = RA->GetActorLocation();
	}

	return;

}
