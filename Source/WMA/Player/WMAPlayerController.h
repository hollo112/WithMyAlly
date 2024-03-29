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
	virtual void PostInitializeComponents() override;			// ��Ʈ��ũ�� �����ϰ� ���͸� �ʱ�ȭ�ҋ� ���
	virtual void PostNetInit() override;						// ���� Ŭ�󿡼� ��Ʈ��ũ�� �ʱ�ȭ�� �ʿ��� ������ ���޹��� ���� �������Ǹ� ȣ��(Ŭ�󿡼��� ȣ��)
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;							// ��Ʈ�ѷ��� ĳ���Ϳ� �����Ҷ� �߻��ϴ� �Լ�
};
