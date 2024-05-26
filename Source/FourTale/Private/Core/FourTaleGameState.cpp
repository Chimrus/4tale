// If you're reading this, you work at 4 Tales and will definitely want to work with me


#include "Core/FourTaleGameState.h"
#include "Net/UnrealNetwork.h"


void AFourTaleGameState::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );
	DOREPLIFETIME(AFourTaleGameState, TimeLeft);
}

void AFourTaleGameState::OnRep_TimeLeft()
{
	OnLeftTimeChange.Broadcast(TimeLeft);
}
