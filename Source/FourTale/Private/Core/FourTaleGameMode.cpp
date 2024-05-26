// Copyright Epic Games, Inc. All Rights Reserved.

#include "FourTale/Public/Core/FourTaleGameMode.h"
#include "Actors/Pawns/Characters/FourTaleCharacter.h"
#include "Core/FourTalePlayerState.h"
#include "UObject/ConstructorHelpers.h"

AFourTaleGameMode::AFourTaleGameMode()
{
	DefaultPawnClass = AFourTaleCharacter::StaticClass();
}

void AFourTaleGameMode::StopRound()
{
	//SetPause(nullptr, false);
}

void AFourTaleGameMode::Killed(AController* KillerController, AController* VictimController)
{
	AFourTalePlayerState* KillerPlayerState = KillerController
											 ? KillerController->GetPlayerState<AFourTalePlayerState>()
											 : nullptr;
	AFourTalePlayerState* VictimPlayerState = VictimController
											 ? VictimController->GetPlayerState<AFourTalePlayerState>()
											 : nullptr;
	if (KillerPlayerState)
	{
		KillerPlayerState->Kills++;
	}
	if (VictimPlayerState)
	{
		VictimPlayerState->Deathes++;
	}
	RestartPlayer(VictimController);
}