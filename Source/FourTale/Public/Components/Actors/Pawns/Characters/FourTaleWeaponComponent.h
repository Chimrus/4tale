#pragma once

#include "CoreMinimal.h"
#include "Actors/FourTaleBaseWeapon.h"
#include "Components/ActorComponent.h"
#include "FourTaleWeaponComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponMakeShotSignature, FWeaponStats&, WeaponStats);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponChangeFireModeSignature, FWeaponStats&, WeaponStats);

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

	UFUNCTION()
	void WeaponActorMakeShot(FWeaponStats& WeaponStats);

	UFUNCTION()
	void WeaponActorChangeFire(FWeaponStats& WeaponStats);
	
	UFUNCTION()
	void BindWeaponDelegates(AFourTaleBaseWeapon* CurrentWeapon);
	UFUNCTION()
	void UnbindWeaponDelegates(AFourTaleBaseWeapon* CurrentWeapon);
	
	void NextWeapon(bool bIsNextWeapon);
	
	void ChangeWeapon(const FInputActionValue& Value);

	UPROPERTY()
	FOnWeaponMakeShotSignature OnWeaponMakeShot;

	UPROPERTY()
	FOnWeaponChangeFireModeSignature OnWeaponChangeFireMode;

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY()
	TArray<AFourTaleBaseWeapon*> Weapons;
	
	UPROPERTY()
	AFourTaleBaseWeapon* CurrentWeapon;
};
