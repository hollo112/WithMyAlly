// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "WMAEnvQueryContext.generated.h"

/**
 * 
 */
UCLASS()
class WMA_API UWMAEnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()
	
public:
	UWMAEnvQueryContext();

	virtual void  ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

	virtual void ProvideSingleActor(UObject* QuerierObject, AActor* QuerierActor, AActor*& ResultingActor);



};
