#pragma once

#include "CoreMinimal.h"
#include "Actors/FourTaleBaseWeapon.h"
#include "Components/ActorComponent.h"
#include "FourTaleWeaponComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponDataChangeSignature, FWeaponStats&, WeaponStats);

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
	void WeaponActorDataChangeHandle(FWeaponStats& WeaponStats);
	
	UFUNCTION()
	void BindWeaponDelegates(AFourTaleBaseWeapon* Weapon);
	
	UFUNCTION()
	void UnbindWeaponDelegates(AFourTaleBaseWeapon* Weapon);

	UFUNCTION()
	void NextWeapon(bool bIsNextWeapon);

	UFUNCTION(Server, Reliable)
	void ServerChangeWeapon(const FInputActionValue& Value);

	UFUNCTION(NetMulticast, Reliable)
	void ChangeWeapon(const FInputActionValue& Value);

	UPROPERTY()
	FOnWeaponDataChangeSignature OnWeaponDataChange;

	UPROPERTY()
	AFourTaleBaseWeapon* CurrentWeapon;

	UPROPERTY()
	TArray<AFourTaleBaseWeapon*> Weapons;

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
