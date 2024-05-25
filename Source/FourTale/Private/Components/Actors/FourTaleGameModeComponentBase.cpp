// If you're reading this, you work at 4 Tales and will definitely want to work with me


#include "Components/Actors/GameMode/FourTaleGameModeComponentBase.h"

#include "Core/FourTaleGameMode.h"
#include "GameFramework/GameModeBase.h"


UFourTaleGameModeComponentBase::UFourTaleGameModeComponentBase()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UFourTaleGameModeComponentBase::BeginPlay()
{
	Super::BeginPlay();
	RoundTimeLeft = RoundTime;
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(RoundTimerHandle, this, &UFourTaleGameModeComponentBase::GameModeComponentTick, true);
	}
}

void UFourTaleGameModeComponentBase::GameModeComponentTick()
{
	RoundTimeLeft--;
	if (RoundTimeLeft <= 0)
	{
		AFourTaleGameMode* GameModeBase = Cast<AFourTaleGameMode>(GetOwner());
		GameModeBase->StopRound();
	}
}

