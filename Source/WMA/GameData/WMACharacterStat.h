
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WMACharacterStat.generated.h"

USTRUCT(BlueprintType)
struct FWMACharacterStat : public FTableRowBase
{
	GENERATED_BODY()

	public:
	FWMACharacterStat() : MaxHp(0.0f), Attack(0.0f), ShortWPRange(0.0f), DisposableWPRange(0.0f), LongWPRange(0.0f), AttackSpeed(0.0f), MovementSpeed(0.0f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float ShortWPRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float DisposableWPRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float LongWPRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MovementSpeed;

	FWMACharacterStat operator+(const FWMACharacterStat& Other) const
	{
		const float* const ThisPtr = reinterpret_cast<const float* const>(this);
		const float* const OtherPtr = reinterpret_cast<const float* const>(&Other);

		FWMACharacterStat Result;
		float* ResultPtr = reinterpret_cast<float*>(&Result);
		int32 StatNum = sizeof(FWMACharacterStat) / sizeof(float);
		for (int32 i = 0; i < StatNum; i++)
		{
			ResultPtr[i] = ThisPtr[i] + OtherPtr[i];
		}

		return Result;
	}
};