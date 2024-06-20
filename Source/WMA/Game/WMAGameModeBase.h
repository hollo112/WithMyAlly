// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interface/WMAGameInterface.h"
#include "WMAGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class WMA_API AWMAGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	public:
	AWMAGameModeBase();

	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;			// Ŭ���� ���� ��û�� ó���ϴ� �Լ�
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;	// ������ ����� Ŭ�� �����ϴ� �÷��̾���Ʈ�ѷ��� ����� �Լ�
	//virtual void PostLogin(APlayerController* NewPlayer) override;																						// �÷��̾� ������ ���� �÷��̾ �ʿ��� �⺻ ������ ��� �������ϴ� �Լ� (���������� ����)
	//virtual void StartPlay() override;	

	//virtual void PostLogin(APlayerController* NewPlayer) override;
	
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	bool ShouldSpawnAtStartSpot(AController* Player) override { return false; };

	void TravelNewMap();
	void Travel15F();
	void TravelTrain1F();
};
