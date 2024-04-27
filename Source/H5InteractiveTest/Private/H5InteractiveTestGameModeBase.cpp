#include "H5InteractiveTestGameModeBase.h"

#include "GameFramework/PlayerState.h"
#include "H5InteractiveTestCharacter.h"
 
void AH5InteractiveTestGameModeBase::OnPlayerHit(AH5InteractiveTestCharacter* InstigatorCharacter, AH5InteractiveTestCharacter* DamagedCharacter)
{
	APlayerState* InstigatorPS = InstigatorCharacter->GetPlayerState();
	const int NewScore = InstigatorPS->GetScore() + PointsPerHit;
	InstigatorPS->SetScore(NewScore);
	InstigatorPS->OnRep_Score(); // Server doesn't call OnRep functions, so we must call it manually.

	const AActor* SpawnPoint = ChoosePlayerStart(DamagedCharacter->GetController());
	DamagedCharacter->SetActorLocationAndRotation(SpawnPoint->GetActorLocation(), SpawnPoint->GetActorRotation());
}
