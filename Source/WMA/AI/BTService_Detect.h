// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "BTService_Detect.generated.h"

/**
 * 
 */
UCLASS()
class WMA_API UBTService_Detect : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_Detect();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	//UINT8 GrowlTime = 0;

private:
	UAIPerceptionComponent* PerceptionComponent;
	UAISenseConfig_Hearing* HearingConfig;

	void SetupPerceptionSystem();
};
