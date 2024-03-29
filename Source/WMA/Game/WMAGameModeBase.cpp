// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/WMAGameModeBase.h"
#include "WMA.h"
#include "WMAGameState.h"

AWMAGameModeBase::AWMAGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Script/Engine.Blueprint'/Game/Characters/BP_WMA_CharacterPlayer.BP_WMA_CharacterPlayer_C'"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/WMA.WMAPlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}

	GameStateClass = AWMAGameState::StaticClass();
}

//void AWMAGameModeBase::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
//{
//	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("=========================================================================="));
//	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("Begin"));
//
//	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
//
//	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("End"));
//}
//
//APlayerController* AWMAGameModeBase::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
//{
//	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("Begin"));
//
//	APlayerController* NewPlayerController = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
//
//	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("End"));
//
//	return NewPlayerController;
//}
//
//void AWMAGameModeBase::PostLogin(APlayerController* NewPlayer)
//{
//	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("Begin"));
//
//	Super::PostLogin(NewPlayer);
//	UNetDriver* NetDriver = GetNetDriver();
//	if (NetDriver)
//	{
//		for (const auto& Connection : NetDriver->ClientConnections)
//		{
//			WMA_LOG(LogWMANetwork, Log, TEXT("Client Connections : %s"), *Connection->GetName());
//		}
//	}
//	else
//	{
//		//NetDriver->ClientConnections.Num();
//		WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("No NetDriver"));
//	}
//	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("End"));
//}
//
//void AWMAGameModeBase::StartPlay()
//{
//	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("Begin"));
//
//	Super::StartPlay();
//
//	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("End"));
//}
