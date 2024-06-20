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

	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;			// 클라의 접속 요청을 처리하는 함수
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;	// 접속을 허용한 클라에 대응하는 플레이어컨트롤러를 만드는 함수
	//virtual void PostLogin(APlayerController* NewPlayer) override;																						// 플레이어 입장을 위해 플레이어에 필요한 기본 설정을 모두 마무리하는 함수 (서버에서만 실행)
	//virtual void StartPlay() override;	

	//virtual void PostLogin(APlayerController* NewPlayer) override;
	
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	bool ShouldSpawnAtStartSpot(AController* Player) override { return false; };

	void TravelNewMap();
	void Travel15F();
	void TravelTrain1F();
};
