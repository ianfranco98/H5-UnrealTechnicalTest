#include "H5InteractiveTestScoreboard.h"

#include "Components/VerticalBox.h"
#include "H5InteractiveTestGameStateBase.h"

#include "H5InteractiveTestPlayerState.h"
#include "H5InteractiveTestPScoreWidget.h"


void UH5InteractiveTestScoreboard::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	AGameStateBase* GameState = GetWorld()->GetGameState();

	if (GameState)
	{
		BindToPlayerArrayUpdates(GameState);
	}
	else
	{
		GetWorld()->GameStateSetEvent.AddUObject(this, &UH5InteractiveTestScoreboard::BindToPlayerArrayUpdates);
	}
}

void UH5InteractiveTestScoreboard::BindToPlayerArrayUpdates(AGameStateBase* GameState)
{
	AH5InteractiveTestGameStateBase* H5ITGameState = CastChecked<AH5InteractiveTestGameStateBase>(GameState);
	H5ITGameState->OnPlayerStateAdded.AddUObject(this, &UH5InteractiveTestScoreboard::OnPlayerArrayUpdated);

	OnPlayerArrayUpdated();
}

void UH5InteractiveTestScoreboard::OnPlayerArrayUpdated()
{
	ListWidget->ClearChildren();

	for (APlayerState* PlayerState : GetWorld()->GetGameState()->PlayerArray)
	{
		AH5InteractiveTestPlayerState* H5ITPlayerState = CastChecked<AH5InteractiveTestPlayerState>(PlayerState);

		UH5InteractiveTestPScoreWidget* PlayerScoreWidget = CreateWidget<UH5InteractiveTestPScoreWidget>(GetOwningPlayer(), PlayerScoreWidgetClass);

		PlayerScoreWidget->InitializeWidget(PlayerState->GetPlayerName(), PlayerState->GetScore());

		H5ITPlayerState->OnScoreUpdated.BindUObject(PlayerScoreWidget, &UH5InteractiveTestPScoreWidget::UpdateScore);

		ListWidget->AddChildToVerticalBox(PlayerScoreWidget);
	}
}
