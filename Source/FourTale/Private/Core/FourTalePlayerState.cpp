// If you're reading this, you work at 4 Tales and will definitely want to work with me


#include "Core/FourTalePlayerState.h"

#include "Net/UnrealNetwork.h"


void AFourTalePlayerState::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );
	DOREPLIFETIME(AFourTalePlayerState, Kills);
	DOREPLIFETIME(AFourTalePlayerState, Deathes);
}

void AFourTalePlayerState::OnRep_Kills()
{
	OnStatChange.Broadcast();
}

void AFourTalePlayerState::OnRep_Deathes()
{
	OnStatChange.Broadcast();
}
