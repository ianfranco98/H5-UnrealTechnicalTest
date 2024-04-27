#include "H5InteractiveTestCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "UObject/ConstructorHelpers.h"

#include "H5InteractiveTestProjectile.h"


AH5InteractiveTestCharacter::AH5InteractiveTestCharacter()
{
	bReplicates = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 600.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	GetCharacterMovement()->MaxWalkSpeed = 450.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetRelativeRotation(FRotator(-70.f, 0.f, 0.f));
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1000.f;
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 6.0f;

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void AH5InteractiveTestCharacter::OnFire()
{
	if (ProjectileClass)
	{
		// Here we could optimize this RPC call limiting client input spam with our bCanShoot timer. For now this is enough.
		ServerRPCHandleFire();
	}
}

void AH5InteractiveTestCharacter::ServerRPCHandleFire_Implementation()
{
	if (bCanShoot)
	{
		FTimerHandle TimeHandler = FTimerHandle();
		bCanShoot = false;
		GetWorldTimerManager().SetTimer(TimeHandler, this, &AH5InteractiveTestCharacter::EnableFire, FireVelocity, false);

		const FRotator SpawnRotation = GetActorForwardVector().Rotation();
		const FVector SpawnLocation = GetActorLocation() + GetActorForwardVector();

		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		ActorSpawnParams.Instigator = GetInstigator();
		ActorSpawnParams.Owner = this;

		GetWorld()->SpawnActor<AH5InteractiveTestProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
	}
}