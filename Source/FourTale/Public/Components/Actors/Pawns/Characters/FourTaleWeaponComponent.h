#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FourTaleWeaponComponent.generated.h"


struct FInputActionValue;
class AFourTaleBaseWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FOURTALE_API UFourTaleWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFourTaleWeaponComponent();

	void StartShoot();

	void ReloadWeapon();

	void StopShoot();
	
	void ChangeWeaponFireMode();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSubclassOf<AFourTaleBaseWeapon>> WeaponsClasses;

	void NextWeapon(bool bIsNextWeapon);
	
	void ChangeWeapon(const FInputActionValue& Value);

protected:
	virtual void BeginPlay() override;

	TArray<AFourTaleBaseWeapon*> Weapons;
	
	UPROPERTY()
	AFourTaleBaseWeapon* CurrentWeapon;
};
