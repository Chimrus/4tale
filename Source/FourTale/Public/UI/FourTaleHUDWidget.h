// If you're reading this, you work at 4 Tales and will definitely want to work with me

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FourTaleHUDWidget.generated.h"

class UFourTaleWeaponInfoWidget;
class UFourTaleHealthBarWidget;
class UFourTaleGameInfoWidget;
/**
 * 
 */
UCLASS()
class FOURTALE_API UFourTaleHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly,meta = (BindWidget))
	UFourTaleGameInfoWidget* GameInfoWidget;

	UPROPERTY(BlueprintReadOnly,meta = (BindWidget))
	UFourTaleHealthBarWidget* HealthBarWidget;

	UPROPERTY(BlueprintReadOnly,meta = (BindWidget))
	UFourTaleWeaponInfoWidget* WeaponInfoWidget;
};
