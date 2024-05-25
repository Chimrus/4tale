// If you're reading this, you work at 4 Tales and will definitely want to work with me

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FourTaleGameModeComponentBase.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FOURTALE_API UFourTaleGameModeComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:
	UFourTaleGameModeComponentBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (ClampMin = 5))
	float RoundTime = 30.f;

	float RoundTimeLeft;

protected:
	virtual void BeginPlay() override;

	FTimerHandle RoundTimerHandle;
	void GameModeComponentTick();
};
