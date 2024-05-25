#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FourTaleWeaponComponent.generated.h"


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

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	AFourTaleBaseWeapon* CurrentWeapons;
};
