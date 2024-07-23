// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/WMABossAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionSystem.h"
#include "WMAAI.h"
#include <Perception/AIPerceptionComponent.h>
#include <Perception/AISenseConfig_Sight.h>
#include <Perception/AISenseConfig_Hearing.h>
#include "AI/BTService_Detect.h"


AWMABossAIController::AWMABossAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(TEXT("/Script/AIModule.BlackboardData'/Game/AI/Boss/BB_WMABoss.BB_WMABoss'"));
	if (nullptr != BBAssetRef.Object)
	{
		BBAsset = BBAssetRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Script/AIModule.BehaviorTree'/Game/AI/Boss/BT_WMABoss.BT_WMABoss'"));
	if (nullptr != BTAssetRef.Object)
	{
		BTAsset = BTAssetRef.Object;
	}

	SetPerceptionSystem();

	if (AIPerceptionComponent) {
		AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AWMABossAIController::OnTargetPerceptionUpdated);
	}
}



void AWMABossAIController::RunAI()
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();
	if (UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsVector(BBKEY_HOMEPOS, GetPawn()->GetActorLocation());

		bool RunResult = RunBehaviorTree(BTAsset);
		ensure(RunResult);
	}

}

void AWMABossAIController::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);		// ���� �����ϰ� �ִ� BT ��������
	if (BTComponent)
	{
		BTComponent->StopTree();
	}
}

void AWMABossAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	//if (Actor && Actor->Tags.Contains("Player"))
	//{
	//	UBlackboardComponent* BlackboardPtr = GetBlackboardComponent();

	//	if (Stimulus.WasSuccessfullySensed())
	//	{
	//		// �÷��̾� ��ġ�� AI ��ġ ������ ���� ���
	//		FVector Direction = Actor->GetActorLocation() - GetPawn()->GetActorLocation();
	//		Direction.Normalize();

	//		// AI ���� ���Ϳ� �÷��̾� ��ġ ������ ���� ���
	//		float DotProduct = FVector::DotProduct(GetPawn()->GetActorForwardVector(), Direction);
	//		float Angle = FMath::Acos(DotProduct);
	//		float AngleDegrees = FMath::RadiansToDegrees(Angle);

	//		// ������ �þ߰� ���� �ִ��� Ȯ��
	//		if (AngleDegrees <= AISenseConfigSight->PeripheralVisionAngleDegrees / 2)
	//		{
	//			UE_LOG(LogTemp, Log, TEXT("InSight"));
	//			BlackboardPtr->SetValueAsObject(BBKEY_TARGET, Actor);
	//			BlackboardPtr->SetValueAsVector("LastKnownPosition", Actor->GetActorLocation());
	//		}
	//			// ���������� ������ ���
	//	}
	//		else
	//		{
	//			// ������ �þ߰� �ۿ� �ִ� ���
	//			HandleLostSight();
	//		}
	//}
	//else
	//{
	//		// �ð� �ڱ��� �������� ���� ���
	//		HandleLostSight();
	//}

	auto SensedClass = UAIPerceptionSystem::GetSenseClassForStimulus(AISenseConfigHearing, Stimulus);
	UBlackboardComponent* BlackboardPtr = GetBlackboardComponent();

	if (Stimulus.WasSuccessfullySensed())
	{
		if (Stimulus.Type == UAISense::GetSenseID<UAISenseConfig_Hearing>())
		{
			const float Distance = FVector::Dist(Stimulus.ReceiverLocation, Stimulus.StimulusLocation);
			if (Distance < AISenseConfigHearing->HearingRange)
			{
				BlackboardPtr->SetValueAsObject(BBKEY_TARGET, Actor);
				//UE_LOG(LogTemp, Log, TEXT("Log Message : %f"), Distance);
			}
		}
	}
}


void AWMABossAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();
}

void AWMABossAIController::HandleLostSight()
{
	UBlackboardComponent* BlackboardPtr = GetBlackboardComponent();
	if (BlackboardPtr)
	{
		BlackboardPtr->ClearValue("TargetActor");
		BlackboardPtr->ClearValue("LastKnownPosition");
		// �߰������� �ؾ� �� ���� �ִٸ� ���⿡ �����մϴ�.
	}
}

void AWMABossAIController::SetPerceptionSystem()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
	AISenseConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>("AI Sight config");
	AISenseConfigHearing = CreateDefaultSubobject<UAISenseConfig_Hearing>("AI Hearing config");

	SetPerceptionComponent(*CreateOptionalDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception")));//

	AISenseConfigSight->SightRadius = 1200.0f;
	AISenseConfigSight->LoseSightRadius = 1700.0f;
	AISenseConfigSight->PeripheralVisionAngleDegrees = 180.0f;
	AISenseConfigSight->DetectionByAffiliation.bDetectEnemies = true;
	AISenseConfigSight->DetectionByAffiliation.bDetectNeutrals = true;
	AISenseConfigSight->DetectionByAffiliation.bDetectFriendlies = true;

	//range ����� ���ľ���
	AISenseConfigHearing->HearingRange = 1200.0f;
	AISenseConfigHearing->LoSHearingRange = 1200.0f;
	AISenseConfigHearing->DetectionByAffiliation.bDetectEnemies = true;
	AISenseConfigHearing->DetectionByAffiliation.bDetectNeutrals = true;
	AISenseConfigHearing->DetectionByAffiliation.bDetectFriendlies = true;

	// Add the Sight Sense to the Perception Component
	AIPerceptionComponent->ConfigureSense(*AISenseConfigSight);
	AIPerceptionComponent->ConfigureSense(*AISenseConfigHearing);




}