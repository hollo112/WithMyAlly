// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WMACharacterStat.h"
#include "WMAGameSingleton.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogWMAGameSingleton, Error, All);

/**
 * 
 */
UCLASS()
class WMA_API UWMAGameSingleton : public UObject
{
	GENERATED_BODY()
	
public:
	UWMAGameSingleton();
	static UWMAGameSingleton& Get();

	// Character Stat Data Section
public:
	FORCEINLINE FWMACharacterStat GetCharacterStat(int32 InLevel) const { return CharacterStatTable.IsValidIndex(InLevel - 1) ? CharacterStatTable[InLevel - 1] : FWMACharacterStat(); }

	UPROPERTY()
	int32 CharacterMaxLevel;

private:
	TArray<FWMACharacterStat> CharacterStatTable;
};
