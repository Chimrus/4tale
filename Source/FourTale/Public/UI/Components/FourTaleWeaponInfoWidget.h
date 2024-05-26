// If you're reading this, you work at 4 Tales and will definitely want to work with me

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Actors/Pawns/Characters/FourTaleWeaponComponent.h"
#include "FourTaleWeaponInfoWidget.generated.h"

class UWidgetSwitcher;
class UTextBlock;
/**
 * 
 */
UCLASS()
class FOURTALE_API UFourTaleWeaponInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void WeaponDataChange(FWeaponStats& WeaponStats);

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* AmmoCount;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UWidgetSwitcher* WeaponFireMode;

	UPROPERTY()
	UFourTaleWeaponComponent* WeaponComponent;
};
