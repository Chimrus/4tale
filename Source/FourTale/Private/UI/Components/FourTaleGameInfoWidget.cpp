// If you're reading this, you work at 4 Tales and will definitely want to work with me


#include "UI/Components/FourTaleGameInfoWidget.h"

#include "Components/TextBlock.h"
#include "Core/FourTaleGameState.h"
#include "Core/FourTalePlayerState.h"

void UFourTaleGameInfoWidget::UpdatePlayerStat()
{
	FText KillsText = FText::FromString(FString::Printf(
		TEXT("Kills: %d"), FourTalePlayerState->GetKills()));
	KillsTextBlock->SetText(KillsText);

	FText DeathesText = FText::FromString(FString::Printf(
		TEXT("Deathes: %d"), FourTalePlayerState->GetDeathes()));
	DeathesTextBlock->SetText(DeathesText);
}

void UFourTaleGameInfoWidget::UpdateGameStat(float TimeLeft)
{
	int32 Minutes = FMath::FloorToInt(TimeLeft / 60);
	int32 Seconds = FMath::FloorToInt(FMath::Fmod(TimeLeft, 60));
	FString TimeString = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
	FText TimeText = FText::FromString(TEXT("Time Left: ") + TimeString);
	TimeRemainingTextBlock->SetText(TimeText);
}

void UFourTaleGameInfoWidget::UpdatePlayerState()
{
	if (FourTalePlayerState)
	{
		FourTalePlayerState->OnStatChange.AddDynamic(this, &UFourTaleGameInfoWidget::UpdatePlayerStat);
		UpdatePlayerStat();
	}
	else
	{
		FTimerHandle ActiveTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(ActiveTimerHandle, this, &UFourTaleGameInfoWidget::UpdatePlayerState, 2);
	}
}

void UFourTaleGameInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();
	FourTalePlayerState = GetOwningPlayer()->GetPlayerState<AFourTalePlayerState>();
	if (FourTalePlayerState)
	{
		FourTalePlayerState->OnStatChange.AddDynamic(this, &UFourTaleGameInfoWidget::UpdatePlayerStat);
		UpdatePlayerStat();
	}
	else
	{
		FTimerHandle ActiveTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(ActiveTimerHandle, this, &UFourTaleGameInfoWidget::UpdatePlayerState, 2);
	}
	TaleGameState = GetWorld()->GetGameState<AFourTaleGameState>();
	if (TaleGameState)
	{
		TaleGameState->OnLeftTimeChange.AddDynamic(this, &UFourTaleGameInfoWidget::UpdateGameStat);
	}
}

void UFourTaleGameInfoWidget::NativeDestruct()
{
	Super::NativeDestruct();
	if (FourTalePlayerState)
	{
		FourTalePlayerState->OnStatChange.RemoveAll(this);
	}
	
	if (TaleGameState)
	{
		TaleGameState->OnLeftTimeChange.RemoveAll(this);
	}
}
