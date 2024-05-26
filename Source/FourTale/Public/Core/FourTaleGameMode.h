// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FourTaleGameState.h"
#include "GameFramework/GameMode.h"
#include "FourTaleGameMode.generated.h"

UCLASS()
class FOURTALE_API AFourTaleGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	
	void RoundCountDown();
	
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	float RoundTime = 90;
	
	float TimeLeft = 90;

	UPROPERTY()
	AFourTaleGameState* FourTaleGameState;
	
	FTimerHandle CountDownTimerHalndle;

	AFourTaleGameMode();
	
	void StopRound();
	
	void Killed(AController* KillerController, AController* VictimController);
};



