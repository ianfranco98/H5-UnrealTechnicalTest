#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "H5InteractiveTestPlayerState.generated.h"

DECLARE_DELEGATE_OneParam(FOnScoreUpdated, float NewScore);

UCLASS()
class H5INTERACTIVETEST_API AH5InteractiveTestPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

	virtual void OnRep_PlayerName() override;

	virtual void OnRep_Score() override;

	FOnScoreUpdated OnScoreUpdated;
};
