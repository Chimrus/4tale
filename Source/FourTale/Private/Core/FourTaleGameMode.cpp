// Copyright Epic Games, Inc. All Rights Reserved.

#include "FourTale/Public/Core/FourTaleGameMode.h"
#include "Actors/Pawns/Characters/FourTaleCharacter.h"
#include "Core/FourTaleGameState.h"
#include "Core/FourTalePlayerState.h"
#include "UObject/ConstructorHelpers.h"

void AFourTaleGameMode::RoundCountDown()
{
	TimeLeft--;
	if (FourTaleGameState)
	{
		FourTaleGameState->TimeLeft = TimeLeft;
	}
	if (TimeLeft<= 0)
	{
		StopRound();
		GetWorldTimerManager().ClearTimer(CountDownTimerHalndle);
	}
}

void AFourTaleGameMode::BeginPlay()
{
	Super::BeginPlay();
	TimeLeft = RoundTime;
	GetWorldTimerManager().SetTimer(CountDownTimerHalndle, this, &AFourTaleGameMode::RoundCountDown, 1, true);
	FourTaleGameState = GetGameState<AFourTaleGameState>();
}

AFourTaleGameMode::AFourTaleGameMode()
{
	DefaultPawnClass = AFourTaleCharacter::StaticClass();
}

void AFourTaleGameMode::StopRound()
{
 
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
		KillerPlayerState->IncreaseKills();
	}
	if (VictimPlayerState)
	{
		VictimPlayerState->IncreaseDeathes();
	}
}