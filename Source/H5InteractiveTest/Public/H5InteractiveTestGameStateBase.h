#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "H5InteractiveTestGameStateBase.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnPlayerStateAdded);


UCLASS()
class H5INTERACTIVETEST_API AH5InteractiveTestGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	void PostInitializeComponents() override;

	virtual void AddPlayerState(APlayerState* PlayerState) override;

	FOnPlayerStateAdded OnPlayerStateAdded;
};
