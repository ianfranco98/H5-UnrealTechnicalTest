#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "H5InteractiveTestPScoreWidget.generated.h"

class UTextBlock;

UCLASS()
class H5INTERACTIVETEST_API UH5InteractiveTestPScoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void InitializeWidget(const FString& Name, float Score);

	void UpdateScore(float Score);

protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> NameText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreText;

};
