#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "H5InteractiveTestGameModeBase.generated.h"

class AH5InteractiveTestCharacter;

UCLASS()
class H5INTERACTIVETEST_API AH5InteractiveTestGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	void OnPlayerHit(AH5InteractiveTestCharacter* InstigatorCharacter, AH5InteractiveTestCharacter* DamagedCharacter);

protected:

	UPROPERTY(EditDefaultsOnly, Category = GameRules)
	float PointsPerHit = 1.0f;
};
