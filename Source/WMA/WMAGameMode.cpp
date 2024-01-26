// Copyright Epic Games, Inc. All Rights Reserved.

#include "WMAGameMode.h"
#include "WMACharacter.h"
#include "UObject/ConstructorHelpers.h"

AWMAGameMode::AWMAGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
