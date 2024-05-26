// If you're reading this, you work at 4 Tales and will definitely want to work with me

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FourTaleBaseWeapon.generated.h"

UENUM(BlueprintType, Blueprintable)
enum class EFiringMode : uint8
{
	FM_Single = 0,
	FM_SemiAuto,
	FM_FullAuto,
	FM_MAX UMETA(Hidden)
};


USTRUCT(BlueprintType)
struct FWeaponStats
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSet<EFiringMode> AvailableFiringMode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 Ammo = 30;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	int32 CurrentAmmo = 30;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	int32 SemiAutoShotsCount = 3;
	
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	int32 SemiAutoShotsDone = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float FireDelay = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float BulletSpread = 2.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float Damage = 25.f;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	EFiringMode CurrentFiringMode;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponActorDataChangeSignature, FWeaponStats&, WeaponStats);


UCLASS()
class FOURTALE_API AFourTaleBaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	AFourTaleBaseWeapon();

	virtual void StartShoot();
	virtual void StopShoot();
	virtual void ReloadWeapon();
	virtual void ChangeWeaponFireMode();
	void InitializeFiringModeToStringMap();
	FString GetFiringModeAsString() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	FWeaponStats WeaponStats;
	void MakeShot();
	void TryToMakeShot();

	UPROPERTY()
	FOnWeaponActorDataChangeSignature OnWeaponActorDataChange;
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	TMap<EFiringMode, FString> FiringModeToStringMap;

	FTimerHandle ShootTimer;
};
