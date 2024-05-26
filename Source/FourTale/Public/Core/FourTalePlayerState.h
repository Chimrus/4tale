// If you're reading this, you work at 4 Tales and will definitely want to work with me

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FourTalePlayerState.generated.h"

UCLASS()
class FOURTALE_API AFourTalePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFourTalePlayerState();

	UPROPERTY()
	int32 Kills = 0;

	UPROPERTY()
	int32 Deathes = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
