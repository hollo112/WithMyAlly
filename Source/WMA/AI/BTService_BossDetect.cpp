// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_BossDetect.h"
#include "WMAAI.h"
#include "AIController.h"
#include "Character/WMACharacterBase.h"
#include "Interface/WMACharacterAIInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h" 
#include "GameFramework/CharacterMovementComponent.h"
#include "CharacterStat/WMACharacterStatComponent.h"
#include "Physics/WMACollsion.h"
#include "DrawDebugHelpers.h"

UBTService_BossDetect::UBTService_BossDetect()
{
    NodeName = TEXT("BossDetect");
    Interval = 1.0f;	// 1초단위로 수행
}

void UBTService_BossDetect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    //GrowlTime = GrowlTime + 1.0f;
     //UE_LOG(LogTemp, Warning, TEXT("%d"), GrowlTime);



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
    float PeripheralVisionAngle = AIPawn->GetPeripheralVisionAngleDegrees();

    TArray<FOverlapResult> OverlapResults;
    FCollisionQueryParams CollisionQueryParam(SCENE_QUERY_STAT(Detect), false, ControllingPawn);
    bResult = World->OverlapMultiByChannel(
        OverlapResults,
        Center,
        FQuat::Identity,
        CCHANNEL_WMAACTION,
        FCollisionShape::MakeSphere(DetectRadius),
        CollisionQueryParam
    );
    APawn* InstigatorPawn = nullptr;

    bool bFoundPlayer = false;
    if (bResult)
    {
        for (auto const& OverlapResult : OverlapResults)
        {
            APawn* Pawn = Cast<APawn>(OverlapResult.GetActor());
            if (Pawn && Pawn->GetController()->IsPlayerController())
            {
                FVector Direction = Pawn->GetActorLocation() - Center;
                Direction.Normalize();
                float DotProduct = FVector::DotProduct(ControllingPawn->GetActorForwardVector(), Direction);
                float Angle = FMath::Acos(DotProduct);
                float AngleDegrees = FMath::RadiansToDegrees(Angle);

                if (AngleDegrees <= PeripheralVisionAngle / 2)
                {
                    if (FVector::Dist(Center, Pawn->GetActorLocation()) <= DetectRadius)
                    {

                        OwnerComp.GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, Pawn);
                        AIPawn->SetMovementSpeed();
                        bFoundPlayer = true;
                        break;
                    }
                }             
            }         
        }
    }

    if (!bFoundPlayer)
    {
        // 플레이어가 감지 범위 밖으로 이동했으므로, 타겟을 리셋하고 속도를 원래대로 조정합니다.
        OwnerComp.GetBlackboardComponent()->ClearValue(BBKEY_TARGET);
        AIPawn->ResetMovementSpeed();
    }
}

