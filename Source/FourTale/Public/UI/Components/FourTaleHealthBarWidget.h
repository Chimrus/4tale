// If you're reading this, you work at 4 Tales and will definitely want to work with me

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Actors/FourTaleHealthComponent.h"
#include "FourTaleHealthBarWidget.generated.h"

class UTextBlock;
class UProgressBar;
/**
 * 
 */
UCLASS()
class FOURTALE_API UFourTaleHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	UPROPERTY(BlueprintReadOnly,meta = (BindWidget))
	UProgressBar* HealthProgressBar;

	UPROPERTY(BlueprintReadOnly,meta = (BindWidget))
	UTextBlock* HealthCount;

	UPROPERTY()
	UFourTaleHealthComponent* HealthComponent;

	void HealthUpdate(float NewHealthValue, float OldHealthValue);
};
