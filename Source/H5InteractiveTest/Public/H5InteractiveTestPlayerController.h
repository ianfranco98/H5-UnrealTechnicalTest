#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "H5InteractiveTestPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
class UNiagaraSystem;

UCLASS()
class AH5InteractiveTestPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AH5InteractiveTestPlayerController();

protected:

	virtual void SetupInputComponent() override;
	
	virtual void BeginPlay();

	void OnSetDestinationTriggered();

	void OnSetDestinationReleased();

	void OnFirePressed();

	UFUNCTION(Server, Reliable)
	void Server_MoveCharacter(FVector Destination);

	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UNiagaraSystem> FXCursor;

	UPROPERTY(EditDefaultsOnly, Category=Input)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly, Category=Input)
	TObjectPtr<UInputAction> SetDestinationClickAction;

	UPROPERTY(EditDefaultsOnly, Category=Input)
	TObjectPtr<UInputAction> FireAction;

private:

	FVector CachedDestination;
};


