// If you're reading this, you work at 4 Tales and will definitely want to work with me

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FourTaleGameInfoWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class FOURTALE_API UFourTaleGameInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(BlueprintReadOnly,meta = (BindWidget))
	UTextBlock* TimeRemainingTextBlock;
};
