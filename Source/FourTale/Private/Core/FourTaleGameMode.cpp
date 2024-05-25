// Copyright Epic Games, Inc. All Rights Reserved.

#include "FourTale/Public/Core/FourTaleGameMode.h"
#include "Actors/Pawns/Characters/FourTaleCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFourTaleGameMode::AFourTaleGameMode()
{
	DefaultPawnClass = AFourTaleCharacter::StaticClass();
}

void AFourTaleGameMode::StopRound()
{
	SetPause(nullptr, false);
}
