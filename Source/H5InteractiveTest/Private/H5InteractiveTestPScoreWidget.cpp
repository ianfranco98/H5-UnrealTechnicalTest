#include "H5InteractiveTestPScoreWidget.h"

#include "Components/TextBlock.h"


void UH5InteractiveTestPScoreWidget::InitializeWidget(const FString& Name, float Score)
{
	NameText->SetText(FText::FromString(Name));
	UpdateScore(Score);
}

void UH5InteractiveTestPScoreWidget::UpdateScore(float Score)
{
	ScoreText->SetText(FText::AsNumber(Score));
}
