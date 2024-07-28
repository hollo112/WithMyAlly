// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BossJumpAttack.h"
#include "AIController.h"
#include "Interface/WMACharacterAIInterface.h"
#include "Character/WMACharacterBoss.h"
#include "WMAAI.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_BossJumpAttack::UBTTask_BossJumpAttack()
{
}

EBTNodeResult::Type UBTTask_BossJumpAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	IWMACharacterAIInterface* AIPawn = Cast<IWMACharacterAIInterface>(ControllingPawn);
	if (nullptr == AIPawn)
	{
		return EBTNodeResult::Failed;
	}

	FAICharacterAttackFinished OnAttackFinished;
	OnAttackFinished.BindLambda(
		[&]()
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	);

	AIPawn->SetAIAttackDelegate(OnAttackFinished);
	//AIPawn->AttackByAI();
	//return EBTNodeResult::InProgress;
	APawn* Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET));
	if (nullptr == Target)
	{
		return EBTNodeResult::Failed;
	}

	AWMACharacterBoss* Boss = Cast<AWMACharacterBoss>(OwnerComp.GetAIOwner()->GetPawn());
	Boss->SetPlayerLoc(Target->GetActorLocation());
	Boss->JumpAttack();

	return EBTNodeResult::Succeeded;
}
