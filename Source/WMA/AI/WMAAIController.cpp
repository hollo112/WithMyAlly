// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/WMAAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionSystem.h"
#include "WMAAI.h"
#include <Perception/AIPerceptionComponent.h>
#include <Perception/AISenseConfig_Sight.h>
#include <Perception/AISenseConfig_Hearing.h>


AWMAAIController::AWMAAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(TEXT("/Script/AIModule.BlackboardData'/Game/AI/BB_WMACharacter.BB_WMACharacter'"));
	if (nullptr != BBAssetRef.Object)
	{
		BBAsset = BBAssetRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Script/AIModule.BehaviorTree'/Game/AI/BT_WMACharacter.BT_WMACharacter'"));
	if (nullptr != BTAssetRef.Object)
	{
		BTAsset = BTAssetRef.Object;
	}

	SetPerceptionSystem();

	if (AIPerceptionComponent) {
		AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AWMAAIController::OnTargetPerceptionUpdated);
	}
}



void AWMAAIController::RunAI()
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();
	if (UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsVector(BBKEY_HOMEPOS, GetPawn()->GetActorLocation());

		bool RunResult = RunBehaviorTree(BTAsset);
		ensure(RunResult);
	}
}

void AWMAAIController::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);		// ���� �����ϰ� �ִ� BT ��������
	if (BTComponent)
	{
		BTComponent->StopTree();
	}
}

void AWMAAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
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

	if (SensedClass)
	{

		BlackboardPtr->SetValueAsObject(BBKEY_TARGET, Actor);
		UE_LOG(LogTemp, Log, TEXT("Hearing"));
	}
}


void AWMAAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();


}

void AWMAAIController::HandleLostSight()
{
	UBlackboardComponent* BlackboardPtr = GetBlackboardComponent();
	if (BlackboardPtr)
	{
		BlackboardPtr->ClearValue("TargetActor");
		BlackboardPtr->ClearValue("LastKnownPosition");
		// �߰������� �ؾ� �� ���� �ִٸ� ���⿡ �����մϴ�.
	}
}

void AWMAAIController::SetPerceptionSystem()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
	AISenseConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>("AI Sight config");
	AISenseConfigHearing = CreateDefaultSubobject<UAISenseConfig_Hearing>("AI Hearing config");


	AISenseConfigSight->SightRadius = 1200.0f;
	AISenseConfigSight->LoseSightRadius = 1700.0f;
	AISenseConfigSight->PeripheralVisionAngleDegrees = 180.0f;
	AISenseConfigSight->DetectionByAffiliation.bDetectEnemies = true;
	AISenseConfigSight->DetectionByAffiliation.bDetectNeutrals = true;
	AISenseConfigSight->DetectionByAffiliation.bDetectFriendlies = true;

	//range ����� ���ľ���
	AISenseConfigHearing->HearingRange = 400.0f;
	//AISenseConfigHearing->LoSHearingRange = 1300.0f;
	AISenseConfigHearing->DetectionByAffiliation.bDetectEnemies = true;
	AISenseConfigHearing->DetectionByAffiliation.bDetectNeutrals = true;
	AISenseConfigHearing->DetectionByAffiliation.bDetectFriendlies = true;

	// Add the Sight Sense to the Perception Component
	AIPerceptionComponent->ConfigureSense(*AISenseConfigSight);
	AIPerceptionComponent->ConfigureSense(*AISenseConfigHearing);


}