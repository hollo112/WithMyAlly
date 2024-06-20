// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/WMAGameModeBase.h"
#include "WMA.h"
#include "WMAGameState.h"
#include "Player/WMAPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "WMAPlayerStart.h"
#include "Engine/World.h"
#include "Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"

AWMAGameModeBase::AWMAGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/BP_WMACharacterPlayer.BP_WMACharacterPlayer_C'"));
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
	PlayerStateClass = AWMAPlayerState::StaticClass();
}


void AWMAGameModeBase::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("=========================================================================="));
	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("Begin"));

	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("End"));
}


AActor* AWMAGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	if (Player)
	{
		AWMAPlayerState* PlayerState = Cast<AWMAPlayerState>(Player->PlayerState);
		UE_LOG(LogTemp, Log, TEXT("choose : %s"), PlayerState->bFemale ? TEXT("true") : TEXT("false"));
		if (PlayerState)
		{
			TArray<AWMAPlayerStart*> Starts;
			for (TActorIterator<AWMAPlayerStart> StartItr(GetWorld()); StartItr; ++StartItr)
			{
				if (StartItr->bFemale == PlayerState->bFemale)
				{
					Starts.Add(*StartItr);
				}
			}

			if (Starts.Num() > 0)
			{
				return Starts[FMath::RandRange(0, Starts.Num() - 1)];
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("No suitable player starts found for the player"));
				return Super::ChoosePlayerStart_Implementation(Player); // 기본 플레이어 시작 위치로 돌아가기
			}
		}
	}

	return nullptr;
}

void AWMAGameModeBase::TravelNewMap()
{
	GetWorld()->ServerTravel(TEXT("/Game/Map/NewMap?listen"));
}

void AWMAGameModeBase::Travel15F()
{
	GetWorld()->ServerTravel(TEXT("/Game/Map/WithMyAlly15F?listen"));
}

void AWMAGameModeBase::TravelTrain1F()
{
	GetWorld()->ServerTravel(TEXT("/Game/Map/WithMyAllyTrain1F?listen"));
}


APlayerController* AWMAGameModeBase::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("Begin"));

	APlayerController* NewPlayerController = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);

	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("End"));

	if (NewPlayerController)
	{
		AWMAPlayerState* PlayerState = Cast<AWMAPlayerState>(NewPlayerController->PlayerState);
		if (PlayerState && GameState)
		{
			uint8 NumFemale = 0;
			uint8 NumMale = 0;
			for (APlayerState* It : GameState->PlayerArray)
			{
				AWMAPlayerState* OtherPs = Cast<AWMAPlayerState>(It);
				if (OtherPs)
				{
					if (OtherPs->bFemale)
					{
						++NumFemale;
					}
					else
					{
						++NumMale;
					}
				}
			}

			if (NumMale > NumFemale)
			{
				PlayerState->bFemale = true;
			}

			/*if (GetNetMode() == ENetMode::NM_ListenServer)
			{
				PlayerState->bFemale = true;
				UE_LOG(LogTemp, Log, TEXT("Log Female"));
			}
			else
			{
				PlayerState->bFemale = false;
				UE_LOG(LogTemp, Log, TEXT("Log Male"));
			}*/
		}
	}

	return NewPlayerController;
}

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

