#include "H5InteractiveTestHUD.h"
#include "H5InteractiveTestScoreboard.h"


void AH5InteractiveTestHUD::BeginPlay()
{
	Super::BeginPlay();

	if (ScoreboardWidgetClass)
	{
		ScoreboardWidget = CreateWidget<UH5InteractiveTestScoreboard>(PlayerOwner.Get(), ScoreboardWidgetClass);
		ScoreboardWidget->AddToViewport();
	}
}


