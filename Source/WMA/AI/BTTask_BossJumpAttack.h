// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_BossJumpAttack.generated.h"

/**
 * 
 */
UCLASS()
class WMA_API UBTTask_BossJumpAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_BossJumpAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
