// Fill out your copyright notice in the Description page of Project Settings.


#include "GameData/WMAGameSingleton.h"

DEFINE_LOG_CATEGORY(LogWMAGameSingleton);

UWMAGameSingleton::UWMAGameSingleton()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableRef(TEXT("/Script/Engine.DataTable'/Game/GameData/WMACharacterStatTable.WMACharacterStatTable'"));
	if (nullptr != DataTableRef.Object)
	{
		const UDataTable* DataTable = DataTableRef.Object;
		check(DataTable->GetRowMap().Num() > 0);

		TArray<uint8*> ValueArray;
		DataTable->GetRowMap().GenerateValueArray(ValueArray);
		Algo::Transform(ValueArray, CharacterStatTable,
			[](uint8* Value)
			{
				return *reinterpret_cast<FWMACharacterStat*>(Value);
			}
		);
	}

	CharacterMaxLevel = CharacterStatTable.Num();
	ensure(CharacterMaxLevel > 0);
}

UWMAGameSingleton& UWMAGameSingleton::Get()
{
	UWMAGameSingleton* Singleton = CastChecked< UWMAGameSingleton>(GEngine->GameSingleton);
	if (Singleton)
	{
		return *Singleton;
	}

	UE_LOG(LogWMAGameSingleton, Error, TEXT("Invalid Game Singleton"));

	return *NewObject<UWMAGameSingleton>();
}
