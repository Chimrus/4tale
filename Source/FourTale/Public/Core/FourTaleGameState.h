// If you're reading this, you work at 4 Tales and will definitely want to work with me

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "FourTaleGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLeftTimeChangeBaseSignature, float, TimeLeft);

UCLASS()
class FOURTALE_API AFourTaleGameState : public AGameState
{
	GENERATED_BODY()

public:
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_TimeLeft)
	float TimeLeft;

	FOnLeftTimeChangeBaseSignature OnLeftTimeChange;

	UFUNCTION()
	void OnRep_TimeLeft();
};
