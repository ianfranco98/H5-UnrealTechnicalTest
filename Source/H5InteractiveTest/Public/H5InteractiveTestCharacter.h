#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "H5InteractiveTestCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

class AH5InteractiveTestProjectile;

UCLASS(Blueprintable)
class AH5InteractiveTestCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AH5InteractiveTestCharacter();

	UFUNCTION(BlueprintCallable)
	void OnFire();

	UFUNCTION(Server, Reliable)
	void ServerRPCHandleFire();

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AH5InteractiveTestProjectile> ProjectileClass;

private:

	void EnableFire() { bCanShoot = true; }
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(EditDefaultsOnly)
	float FireVelocity = 0.12f;

	bool bCanShoot = true;
};

