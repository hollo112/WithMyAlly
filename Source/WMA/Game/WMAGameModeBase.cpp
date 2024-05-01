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
	PlayerStateClass = AWMAPlayerState::StaticClass();
}


void AWMAGameModeBase::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("=========================================================================="));
	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("Begin"));

	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

	WMA_LOG(LogWMANetwork, Log, TEXT("%s"), TEXT("End"));
}

//void AWMAGameModeBase::StartPlay()
//{
//	/*for (APlayerStart* PlayerStart : TActorRange<APlayerStart>(GetWorld()))
//	{
//		PlayerStartArray.Add(PlayerStart);
//	}*/
//}

void AWMAGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (NewPlayer)
	{
		AWMAPlayerState* PlayerState = Cast<AWMAPlayerState>(NewPlayer->PlayerState);
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
				UE_LOG(LogTemp, Log, TEXT("Log Female true"));
			}


			UE_LOG(LogTemp, Log, TEXT("post : %s"), PlayerState->bFemale ? TEXT("true") : TEXT("false"));
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
}

AActor* AWMAGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	if (Player)
	{
		AWMAPlayerState *PlayerState = Cast<AWMAPlayerState>(Player->PlayerState);
		UE_LOG(LogTemp, Log, TEXT("choose : %s"), PlayerState->bFemale ? TEXT("true") : TEXT("false"));
		if (PlayerState)
		{
			TArray<AWMAPlayerStart *> Starts;
			for (TActorIterator<AWMAPlayerStart> StartItr(GetWorld()); StartItr; ++StartItr) 
			{
				if (StartItr->bFemale == PlayerState->bFemale) {
					Starts.Add(*StartItr);
					UE_LOG(LogTemp, Log, TEXT("choose : add"));
				}
			}

			return Starts[FMath::RandRange(0, Starts.Num() - 1)];
		}
	}

	return NULL;
}

//FTransform AWMAGameModeBase::GetPlayerStart(bool bFemale) const
//{
//	if (bFemale)
//	{
//		for (int32 Index = 0; Index != PlayerStartArray.Num(); ++Index)
//		{
//			AWMAPlayerState* PlayerState = Cast<AWMAPlayerState>(PlayerStartArray[Index]);
//			if (PlayerState->bFemale)
//			{
//				return PlayerStartArray[Index]->GetActorTransform();
//			}
//		}
//	}
//	else
//	{
//		for (int32 Index = 0; Index != PlayerStartArray.Num(); ++Index)
//		{
//			AWMAPlayerState* PlayerState = Cast<AWMAPlayerState>(PlayerStartArray[Index]);
//			if (!PlayerState->bFemale)
//			{
//				return PlayerStartArray[Index]->GetActorTransform();
//			}
//		}
//	}
//
//	return FTransform();
//}
//


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

