// If you're reading this, you work at 4 Tales and will definitely want to work with me


#include "UI/Components/FourTaleWeaponInfoWidget.h"

#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Actors/Pawns/Characters/FourTaleWeaponComponent.h"

void UFourTaleWeaponInfoWidget::ChangeFireMode(FWeaponStats& WeaponStats)
{
	WeaponFireMode->SetActiveWidgetIndex(static_cast<int32>(WeaponStats.CurrentFiringMode));
}

void UFourTaleWeaponInfoWidget::WeaponMakeShot(FWeaponStats& WeaponStats)
{
	FText AmmoText = FText::FromString(FString::Printf(TEXT("%d / %d"), WeaponStats.CurrentAmmo, WeaponStats.Ammo));
	AmmoCount->SetText(AmmoText);
}
a
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
	WeaponComponent->OnWeaponChangeFireMode.AddDynamic(this, &UFourTaleWeaponInfoWidget::ChangeFireMode);
	WeaponComponent->OnWeaponMakeShot.AddDynamic(this, &UFourTaleWeaponInfoWidget::WeaponMakeShot);
}

void UFourTaleWeaponInfoWidget::NativeDestruct()
{
	Super::NativeDestruct();
}
