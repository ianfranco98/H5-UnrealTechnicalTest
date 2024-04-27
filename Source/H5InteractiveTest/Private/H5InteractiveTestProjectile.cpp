#include "H5InteractiveTestProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"

#include "H5InteractiveTestCharacter.h"
#include "H5InteractiveTestGameModeBase.h"


AH5InteractiveTestProjectile::AH5InteractiveTestProjectile()
{
	bReplicates = true;
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(10.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->IgnoreActorWhenMoving(this, true);
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	RootComponent = CollisionComp;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 2000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	ProjectileMovement->ProjectileGravityScale = 0.0f;

	InitialLifeSpan = 20.0f;
}

void AH5InteractiveTestProjectile::BeginPlay()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		AH5InteractiveTestCharacter* InstigatorCharacter = GetInstigator<AH5InteractiveTestCharacter>();
		InstigatorCharacter->GetCapsuleComponent()->IgnoreActorWhenMoving(this, true);

		CollisionComp->IgnoreActorWhenMoving(InstigatorCharacter, true);
		CollisionComp->OnComponentBeginOverlap.AddUniqueDynamic(this, &AH5InteractiveTestProjectile::OnBeginOverlap);

		CollisionComp->OnComponentHit.AddUniqueDynamic(this, &AH5InteractiveTestProjectile::OnHit);
	}

	Super::BeginPlay();
}

void AH5InteractiveTestProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AH5InteractiveTestCharacter* InstigatorCharacter = Cast<AH5InteractiveTestCharacter>(GetInstigator());
	AH5InteractiveTestCharacter* DamagedCharacter = Cast<AH5InteractiveTestCharacter>(Other);

	if (InstigatorCharacter && DamagedCharacter)
	{
		AH5InteractiveTestGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AH5InteractiveTestGameModeBase>();

		if (ensure(GameMode))
		{
			GameMode->OnPlayerHit(InstigatorCharacter, DamagedCharacter);
		}
	}

	Destroy();
}

void AH5InteractiveTestProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
}

