// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_Detect.h"
#include "WMAAI.h"
#include "AIController.h"
#include "Interface/WMACharacterAIInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CharacterStat/WMACharacterStatComponent.h"
#include "Physics/WMACollsion.h"
#include "DrawDebugHelpers.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;																							// 1초단위로 수행
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)		
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
	{
		return;
	}

	FVector Center = ControllingPawn->GetActorLocation();
	UWorld* World = ControllingPawn->GetWorld();
	if (nullptr == World)
	{
		return;
	}

	IWMACharacterAIInterface* AIPawn = Cast<IWMACharacterAIInterface>(ControllingPawn);
	if (nullptr == AIPawn)
	{
		return;
	}

	float DetectRadius = AIPawn->GetAIDetectRange();

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(SCENE_QUERY_STAT(Detect), false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		CCHANNEL_WMAACTION,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	bool bFoundPlayer = false;
	if (bResult)
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			ACharacter* player = Cast<ACharacter>(ControllingPawn);
			player->GetCharacterMovement()->MaxWalkSpeed = 150;
			APawn* Pawn = Cast<APawn>(OverlapResult.GetActor());
			if (Pawn && Pawn->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, Pawn);
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);

				DrawDebugPoint(World, Pawn->GetActorLocation(), 10.0f, FColor::Green, false, 0.2f);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), Pawn->GetActorLocation(), FColor::Green, false, 0.27f);

				bFoundPlayer = true;
				break;
			}
		}
	}

	if (!bFoundPlayer)
	{
		// 감지된 플레이어가 없으니 타겟을 리셋합니다.
		ACharacter* player = Cast<ACharacter>(ControllingPawn);
		player->GetCharacterMovement()->MaxWalkSpeed = 50;
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, nullptr);
		DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
	}

}
