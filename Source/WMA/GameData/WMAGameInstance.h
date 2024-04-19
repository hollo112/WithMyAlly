// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "WMAGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class WMA_API UWMAGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Default")
	bool InteractItem = false;
};
