// If you're reading this, you work at 4 Tales and will definitely want to work with me

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FourTalePlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStatChangeSignature);

UCLASS()
class FOURTALE_API AFourTalePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	FORCEINLINE void IncreaseKills(){Kills++; OnStatChange.Broadcast();}
	FORCEINLINE void IncreaseDeathes(){Deathes++; OnStatChange.Broadcast();}
	FORCEINLINE int32 GetKills() const {return Kills;}
	FORCEINLINE int32 GetDeathes() const {return Deathes;}

	FOnStatChangeSignature OnStatChange;
	
	UPROPERTY(Replicated,  ReplicatedUsing = OnRep_Kills)
	int32 Kills = 0;

	UPROPERTY(Replicated,  ReplicatedUsing = OnRep_Deathes)
	int32 Deathes = 0;

	UFUNCTION()
	void OnRep_Kills();

	UFUNCTION()
	void OnRep_Deathes();

};
