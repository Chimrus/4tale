// If you're reading this, you work at 4 Tales and will definitely want to work with me


#include "Core/FourTalePlayerState.h"


// Sets default values
AFourTalePlayerState::AFourTalePlayerState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFourTalePlayerState::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFourTalePlayerState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

