// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ABItemData.generated.h"

UENUM(BlueprintType)
enum class EItemType :uint8 {

	ShortWeapon = 0,
	DisposableWeapon = 1,
	LongWeapon = 2,
	NoWeapon = 3
};

/**
 * 
 */
UCLASS()
class WMA_API UABItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Type)
	EItemType Type;
};
