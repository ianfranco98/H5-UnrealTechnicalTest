#include "H5InteractiveTestGameStateBase.h"

void AH5InteractiveTestGameStateBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AH5InteractiveTestGameStateBase::AddPlayerState(APlayerState* PlayerState)
{
	Super::AddPlayerState(PlayerState);

	OnPlayerStateAdded.Broadcast();
}
