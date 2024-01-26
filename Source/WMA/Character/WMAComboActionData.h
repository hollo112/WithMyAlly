// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WMAComboActionData.generated.h"

/**
 * 
 */
UCLASS()
class WMA_API UWMAComboActionData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UWMAComboActionData();

	UPROPERTY(EditAnyWhere, Category = Name)
	FString MontageSectionNamePrefix;

	UPROPERTY(EditAnyWhere, Category = Name)
	uint8 MaxComboCount;

	UPROPERTY(EditAnyWhere, Category = Name)
	float FrameRate;

	UPROPERTY(EditAnyWhere, Category = ComboData)
	TArray<float> EffectiveFrameCount;
};
