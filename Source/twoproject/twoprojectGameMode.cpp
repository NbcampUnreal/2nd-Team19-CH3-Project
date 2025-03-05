// Copyright Epic Games, Inc. All Rights Reserved.

#include "twoprojectGameMode.h"
#include "twoprojectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AtwoprojectGameMode::AtwoprojectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
