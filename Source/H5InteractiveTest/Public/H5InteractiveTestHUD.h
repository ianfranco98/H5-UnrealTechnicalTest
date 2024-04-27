#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "H5InteractiveTestHUD.generated.h"

class UH5InteractiveTestScoreboard;

UCLASS()
class H5INTERACTIVETEST_API AH5InteractiveTestHUD : public AHUD
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

protected:
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UH5InteractiveTestScoreboard> ScoreboardWidgetClass;

	UPROPERTY(Transient)
	TObjectPtr<UH5InteractiveTestScoreboard> ScoreboardWidget;
};
