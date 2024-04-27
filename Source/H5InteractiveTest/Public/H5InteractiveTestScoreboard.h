#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "H5InteractiveTestScoreboard.generated.h"

class UVerticalBox;

class UH5InteractiveTestPScoreWidget;

UCLASS()
class H5INTERACTIVETEST_API UH5InteractiveTestScoreboard : public UUserWidget
{
	GENERATED_BODY()
	
	void NativeOnInitialized() override;

	void BindToPlayerArrayUpdates(AGameStateBase* GameState);

	void OnPlayerArrayUpdated();

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UH5InteractiveTestPScoreWidget> PlayerScoreWidgetClass;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> ListWidget;
};
