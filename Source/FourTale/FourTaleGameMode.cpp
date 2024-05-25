// Copyright Epic Games, Inc. All Rights Reserved.

#include "FourTaleGameMode.h"
#include "FourTaleCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFourTaleGameMode::AFourTaleGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
