// If you're reading this, you work at 4 Tales and will definitely want to work with me


#include "Actors/FourTaleBaseWeapon.h"

DEFINE_LOG_CATEGORY_STATIC(BaseWeaponLog, All,All)

// Sets default values
AFourTaleBaseWeapon::AFourTaleBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AFourTaleBaseWeapon::StartShoot()
{
	
}

void AFourTaleBaseWeapon::StopShoot()
{
}

void AFourTaleBaseWeapon::ReloadWeapon()
{
}

void AFourTaleBaseWeapon::ChangeWeaponFireMode()
{
	TArray<EFiringMode> ModesArray = WeaponStats.AvailableFiringMode.Array();
	int32 CurrentIndex = ModesArray.IndexOfByKey(WeaponStats.CurrentFiringMode);

	if (CurrentIndex == INDEX_NONE || ModesArray.Num() == 0)
	{
		UE_LOG(BaseWeaponLog, Warning, TEXT("%hs ModesArray is empty"), __FUNCTION__)
		return;
	}
	int32 NextIndex = (CurrentIndex + 1) % ModesArray.Num();
	WeaponStats.CurrentFiringMode = ModesArray[NextIndex];
	UE_LOG(BaseWeaponLog, Display, TEXT("%s now current weapon fire mode"), *GetFiringModeAsString());
}

void AFourTaleBaseWeapon::InitializeFiringModeToStringMap()
{
	FiringModeToStringMap.Add(EFiringMode::FM_Single, TEXT("Single Fire"));
	FiringModeToStringMap.Add(EFiringMode::FM_SemiAuto, TEXT("Semi-Automatic"));
	FiringModeToStringMap.Add(EFiringMode::FM_FullAuto, TEXT("Full Automatic"));
}

FString AFourTaleBaseWeapon::GetFiringModeAsString() const
{
	const FString* FiringModeString = FiringModeToStringMap.Find(WeaponStats.CurrentFiringMode);
	if (FiringModeString)
	{
		return *FiringModeString;
	}
	return FString("Unknown");
}

void AFourTaleBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	InitializeFiringModeToStringMap();
	if (WeaponStats.AvailableFiringMode.Array().IsEmpty())
	{
		WeaponStats.AvailableFiringMode.Add(EFiringMode::FM_Single);
		UE_LOG(BaseWeaponLog, Warning, TEXT("%hs Available Firing Mode is empty in %s"), __FUNCTION__, *this->GetClass()->GetName())
	}
	WeaponStats.CurrentFiringMode = WeaponStats.AvailableFiringMode.Array()[0];
}

// Called every frame
void AFourTaleBaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

