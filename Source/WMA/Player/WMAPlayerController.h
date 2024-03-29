// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WMAPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class WMA_API AWMAPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AWMAPlayerController();
	
protected:
	virtual void PostInitializeComponents() override;			// 네트워크와 무관하게 액터를 초기화할떄 사용
	virtual void PostNetInit() override;						// 원격 클라에서 네트워크로 초기화에 필요한 정보를 전달받은 것이 마무리되면 호출(클라에서만 호출)
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;							// 컨트롤러가 캐릭터에 빙의할때 발생하는 함수
};
