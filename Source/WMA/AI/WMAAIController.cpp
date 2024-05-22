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
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);		// 지금 동작하고 있는 BT 가져오기
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
	//		// 플레이어 위치와 AI 위치 사이의 벡터 계산
	//		FVector Direction = Actor->GetActorLocation() - GetPawn()->GetActorLocation();
	//		Direction.Normalize();

	//		// AI 전방 벡터와 플레이어 위치 사이의 각도 계산
	//		float DotProduct = FVector::DotProduct(GetPawn()->GetActorForwardVector(), Direction);
	//		float Angle = FMath::Acos(DotProduct);
	//		float AngleDegrees = FMath::RadiansToDegrees(Angle);

	//		// 각도가 시야각 내에 있는지 확인
	//		if (AngleDegrees <= AISenseConfigSight->PeripheralVisionAngleDegrees / 2)
	//		{
	//			UE_LOG(LogTemp, Log, TEXT("InSight"));
	//			BlackboardPtr->SetValueAsObject(BBKEY_TARGET, Actor);
	//			BlackboardPtr->SetValueAsVector("LastKnownPosition", Actor->GetActorLocation());
	//		}
	//			// 성공적으로 감지된 경우
	//	}
	//		else
	//		{
	//			// 각도가 시야각 밖에 있는 경우
	//			HandleLostSight();
	//		}
	//}
	//else
	//{
	//		// 시각 자극을 감지하지 못한 경우
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
		// 추가적으로 해야 할 일이 있다면 여기에 구현합니다.
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

	//range 변경시 고쳐야함
	AISenseConfigHearing->HearingRange = 400.0f;
	//AISenseConfigHearing->LoSHearingRange = 1300.0f;
	AISenseConfigHearing->DetectionByAffiliation.bDetectEnemies = true;
	AISenseConfigHearing->DetectionByAffiliation.bDetectNeutrals = true;
	AISenseConfigHearing->DetectionByAffiliation.bDetectFriendlies = true;

	// Add the Sight Sense to the Perception Component
	AIPerceptionComponent->ConfigureSense(*AISenseConfigSight);
	AIPerceptionComponent->ConfigureSense(*AISenseConfigHearing);


}