// If you're reading this, you work at 4 Tales and will definitely want to work with me


#include "UI/Components/FourTaleHealthBarWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Actors/FourTaleHealthComponent.h"

void UFourTaleHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	APawn* Pawn = GetOwningPlayer()->GetPawn();
	if (!Pawn)
	{
		return;
	}
	HealthComponent = Pawn->GetComponentByClass<UFourTaleHealthComponent>();
	if (!HealthComponent)
	{
		return;
	}
	HealthComponent->OnHealthChange.AddDynamic(this, &UFourTaleHealthBarWidget::HealthUpdate);
	HealthUpdate(HealthComponent->GetHealth(),HealthComponent->GetHealth());
}

void UFourTaleHealthBarWidget::NativeDestruct()
{
	Super::NativeDestruct();
	HealthComponent->OnHealthChange.RemoveAll(this);
}

void UFourTaleHealthBarWidget::HealthUpdate(float NewHealthValue, float OldHealthValue)
{
	HealthProgressBar->SetPercent(HealthComponent->GetHealthPercent());
	FLinearColor HealthColor = FMath::Lerp(FLinearColor::Red, FLinearColor::Green, HealthComponent->GetHealthPercent());
	HealthProgressBar->SetFillColorAndOpacity(HealthColor);
	FText HealthText = FText::FromString(FString::Printf(
		TEXT("%d / %d"),
		FMath::RoundToInt(NewHealthValue),
		FMath::RoundToInt(HealthComponent->GetMaxHealth())));
	HealthCount->SetText(HealthText);
}
