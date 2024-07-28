// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_BossJumpAttackRange.h"
#include "WMAAI.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/WMACharacterAIInterface.h"
#include "Character/WMACharacterBoss.h"

UBTDecorator_BossJumpAttackRange::UBTDecorator_BossJumpAttackRange()
{
	NodeName = TEXT("CanJumpAttack");
}

bool UBTDecorator_BossJumpAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return false;
	}

	IWMACharacterAIInterface* AIPawn = Cast<IWMACharacterAIInterface>(ControllingPawn);
	if (nullptr == AIPawn)
	{
		return false;
	}

	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET));
	if (nullptr == Target)
	{
		return false;
	}

	float DistanceToTarget = ControllingPawn->GetDistanceTo(Target);
	//점프공격 판정 범위
	float AttackRangeWithRadius = 300.0f;
	bResult = (AttackRangeWithRadius <= DistanceToTarget);
	UE_LOG(LogTemp, Log, TEXT("Character is Die :: %s"), bResult ? TEXT("true") : TEXT("false"));
	return bResult;
}
