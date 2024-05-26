// If you're reading this, you work at 4 Tales and will definitely want to work with me


#include "UI/Components/FourTaleWeaponInfoWidget.h"

#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Actors/Pawns/Characters/FourTaleWeaponComponent.h"

void UFourTaleWeaponInfoWidget::WeaponDataChange(FWeaponStats& WeaponStats)
{
	WeaponFireMode->SetActiveWidgetIndex(static_cast<int32>(WeaponStats.CurrentFiringMode));
	FText AmmoText = FText::FromString(FString::Printf(TEXT("%d / %d"), WeaponStats.CurrentAmmo, WeaponStats.Ammo));
	AmmoCount->SetText(AmmoText);
}

void UFourTaleWeaponInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();
	APawn* Pawn = GetOwningPlayer()->GetPawn();
	if (!Pawn)
	{
		return;
	}
	WeaponComponent = Pawn->GetComponentByClass<UFourTaleWeaponComponent>();
	if (!WeaponComponent)
	{
		return;
	}
	WeaponComponent->OnWeaponDataChange.AddDynamic(this, &UFourTaleWeaponInfoWidget::WeaponDataChange);
	if (WeaponComponent->CurrentWeapon)
	{
		WeaponDataChange(WeaponComponent->CurrentWeapon->WeaponStats);
	}
}

void UFourTaleWeaponInfoWidget::NativeDestruct()
{
	Super::NativeDestruct();
	WeaponComponent->OnWeaponDataChange.RemoveAll(this);
}
