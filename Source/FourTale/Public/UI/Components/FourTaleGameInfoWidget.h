// If you're reading this, you work at 4 Tales and will definitely want to work with me

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Core/FourTalePlayerState.h"
#include "FourTaleGameInfoWidget.generated.h"

class AFourTaleGameState;
class UTextBlock;
/**
 * 
 */
UCLASS()
class FOURTALE_API UFourTaleGameInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void UpdatePlayerStat();
	
	UFUNCTION()
	void UpdateGameStat(float TimeLeft);

	void UpdatePlayerState();
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(BlueprintReadOnly,meta = (BindWidget))
	UTextBlock* TimeRemainingTextBlock;

	UPROPERTY(BlueprintReadOnly,meta = (BindWidget))
	UTextBlock* KillsTextBlock;

	UPROPERTY(BlueprintReadOnly,meta = (BindWidget))
	UTextBlock* DeathesTextBlock;

	UPROPERTY()
	AFourTalePlayerState* FourTalePlayerState;
	
	UPROPERTY()
	AFourTaleGameState* TaleGameState;
};
