#include "H5InteractiveTestPlayerState.h"
#include "H5InteractiveTestGameStateBase.h"

void AH5InteractiveTestPlayerState::OnRep_PlayerName()
{
	Super::OnRep_PlayerName();

	AH5InteractiveTestGameStateBase* GameState = GetWorld()->GetGameState<AH5InteractiveTestGameStateBase>();
	ENetMode netMode = GetNetMode();
	// note: OnRep_PlayerName could be called before and after GameState exist on clients.
	// To keep it simple and because it seems enough, I opted to just ignore the calls where GameState is null.
	if (GameState)
	{
		GameState->OnPlayerStateAdded.Broadcast();
	}
}

void AH5InteractiveTestPlayerState::OnRep_Score()
{
	OnScoreUpdated.ExecuteIfBound(GetScore());
}
