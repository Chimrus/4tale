// If you're reading this, you work at 4 Tales and will definitely want to work with me


#include "Actors/FourTaleBaseWeapon.h"

#include "GameFramework/Character.h"

DEFINE_LOG_CATEGORY_STATIC(BaseWeaponLog, All, All)

// Sets default values
AFourTaleBaseWeapon::AFourTaleBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AFourTaleBaseWeapon::StartShoot()
{
	const auto World = GetWorld();
	if (!World)
	{
		UE_LOG(BaseWeaponLog, Warning, TEXT("%hs World not valid"), __FUNCTION__)
		return;
	}
	World->GetTimerManager().SetTimer(ShootTimer, this, &AFourTaleBaseWeapon::TryToMakeShot, WeaponStats.FireDelay,
	                                  true);
	TryToMakeShot();
}

void AFourTaleBaseWeapon::StopShoot()
{
	GetWorldTimerManager().ClearTimer(ShootTimer);
	WeaponStats.SemiAutoShotsDone = 0;
}

void AFourTaleBaseWeapon::ReloadWeapon()
{
	WeaponStats.CurrentAmmo = WeaponStats.Ammo;
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
	OnWeaponActorChangeFireMode.Broadcast(WeaponStats);
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

void AFourTaleBaseWeapon::MakeShot()
{
	ACharacter* Player = Cast<ACharacter>(GetOwner());
	if (!Player)
	{
		UE_LOG(BaseWeaponLog, Warning, TEXT("%hs Player not valid"), __FUNCTION__)
		return;
	}
	AController* Controller = Player->GetController<AController>();
	if (!Controller)
	{
		UE_LOG(BaseWeaponLog, Warning, TEXT("%hs Controller not valid"), __FUNCTION__)
		return;
	}
	FVector ViewLocation;
	FRotator ViewRotation;
	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	FVector TraceStart = ViewLocation;
	float ConeHalfAngleRad = FMath::DegreesToRadians(WeaponStats.BulletSpread);
	FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), ConeHalfAngleRad);
	FVector TraceEnd = TraceStart + ShootDirection * 100000;
	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());
	if (!GetWorld())
	{
		UE_LOG(BaseWeaponLog, Warning, TEXT("%hs world not valid"), __FUNCTION__)
		return;
	}
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, Params);
	DrawDebugLine(GetWorld(),TraceStart, TraceEnd, FColor::Red, false, 5, 0 ,20);
	WeaponStats.CurrentAmmo--;
	UE_LOG(BaseWeaponLog, Display, TEXT("%hs pew! ammo %d"), __FUNCTION__, WeaponStats.CurrentAmmo)
}

void AFourTaleBaseWeapon::TryToMakeShot()
{
	if (WeaponStats.CurrentAmmo <= 0 || WeaponStats.SemiAutoShotsDone >= WeaponStats.SemiAutoShotsCount)
	{
		GetWorldTimerManager().ClearTimer(ShootTimer);
		return;
	}

	switch (WeaponStats.CurrentFiringMode)
	{
	case EFiringMode::FM_Single: MakeShot();
		GetWorldTimerManager().ClearTimer(ShootTimer);
		break;
	case EFiringMode::FM_SemiAuto: WeaponStats.SemiAutoShotsDone++;
		MakeShot();
		break;
	case EFiringMode::FM_FullAuto: MakeShot();
		break;
	case EFiringMode::FM_MAX: break;
	default: ;
	}
}

void AFourTaleBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	InitializeFiringModeToStringMap();
	if (WeaponStats.AvailableFiringMode.Array().IsEmpty())
	{
		WeaponStats.AvailableFiringMode.Add(EFiringMode::FM_Single);
		UE_LOG(BaseWeaponLog, Warning, TEXT("%hs Available Firing Mode is empty in %s"), __FUNCTION__,
		       *this->GetClass()->GetName())
	}
	WeaponStats.CurrentFiringMode = WeaponStats.AvailableFiringMode.Array()[0];
}

// Called every frame
void AFourTaleBaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
