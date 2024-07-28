// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_BossJumpAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class WMA_API UBTDecorator_BossJumpAttackRange : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_BossJumpAttackRange();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
