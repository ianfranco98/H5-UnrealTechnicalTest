#include "H5InteractiveTestPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "H5InteractiveTestCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AH5InteractiveTestPlayerController::AH5InteractiveTestPlayerController()
{
	bReplicates = true;
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
}

void AH5InteractiveTestPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AH5InteractiveTestPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AH5InteractiveTestPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AH5InteractiveTestPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AH5InteractiveTestPlayerController::OnSetDestinationReleased);

		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &AH5InteractiveTestPlayerController::OnFirePressed);
	}
}

void AH5InteractiveTestPlayerController::OnSetDestinationTriggered()
{
	FHitResult Hit;
	bool bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}
}

void AH5InteractiveTestPlayerController::OnSetDestinationReleased()
{
	if (GetNetMode() == ENetMode::NM_Client)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
	}

	Server_MoveCharacter(CachedDestination);

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
}

void AH5InteractiveTestPlayerController::OnFirePressed()
{
	AH5InteractiveTestCharacter* H5ITCharacter = CastChecked<AH5InteractiveTestCharacter>(GetPawn());
	H5ITCharacter->OnFire();
}

void AH5InteractiveTestPlayerController::Server_MoveCharacter_Implementation(FVector Destination)
{
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Destination);
}
