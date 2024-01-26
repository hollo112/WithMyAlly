// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/WMACharacterBase.h"
#include "WMACharacterNonePlayer.generated.h"

/**
 * 
 */
UCLASS()
class WMA_API AWMACharacterNonePlayer : public AWMACharacterBase
{
	GENERATED_BODY()
	
public:
	AWMACharacterNonePlayer();

protected:
	void SetDead() override;
	float DeadEventDelayTime = 5.0f;	// ���ʵڿ� ������� �ϱ����� ����
};
