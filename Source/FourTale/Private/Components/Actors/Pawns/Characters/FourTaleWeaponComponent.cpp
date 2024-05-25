// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Actors/Pawns/Characters/FourTaleWeaponComponent.h"

#include "InputActionValue.h"
#include "Actors/FourTaleBaseWeapon.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All)


UFourTaleWeaponComponent::UFourTaleWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UFourTaleWeaponComponent::StartShoot()
{
	UE_LOG(LogWeaponComponent, Display, TEXT("%hs"), __FUNCTION__);
	CurrentWeapon->StartShoot();
}

void UFourTaleWeaponComponent::ReloadWeapon()
{
	UE_LOG(LogWeaponComponent, Display, TEXT("%hs"), __FUNCTION__);
	CurrentWeapon->ReloadWeapon();
}

void UFourTaleWeaponComponent::StopShoot()
{
	UE_LOG(LogWeaponComponent, Display, TEXT("%hs"), __FUNCTION__);
	CurrentWeapon->StopShoot();
}

void UFourTaleWeaponComponent::ChangeWeaponFireMode()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, *FString::Printf(TEXT("Change Weapon Fire Mode")));
	if (!CurrentWeapon)
	{
		UE_LOG(LogWeaponComponent, Warning, TEXT("%hs CurrentWeapons is nullptr"), __FUNCTION__);
		return;
	}
	CurrentWeapon->ChangeWeaponFireMode();
}


void UFourTaleWeaponComponent::NextWeapon(bool bIsNextWeapon)
{
	int32 CurrentIndex = Weapons.IndexOfByKey(CurrentWeapon);
	if (CurrentIndex != INDEX_NONE)
	{
		int32 NextIndex = bIsNextWeapon ? (CurrentIndex + 1) % Weapons.Num() : (CurrentIndex - 1 + Weapons.Num()) % Weapons.Num();
		CurrentWeapon->SetActorHiddenInGame(true);
		CurrentWeapon = Weapons[NextIndex];
		CurrentWeapon->SetActorHiddenInGame(false);
		UE_LOG(LogWeaponComponent, Display, TEXT("%hs, %s: CurrentWeapon changed to %s"), __FUNCTION__, bIsNextWeapon ? TEXT("true") : TEXT("false"), *CurrentWeapon->GetName());
	}
	else
	{
		UE_LOG(LogWeaponComponent, Warning, TEXT("%hs: CurrentWeapon is not in the Weapons array"), __FUNCTION__);
	}
	
}

void UFourTaleWeaponComponent::ChangeWeapon(const FInputActionValue& Value)
{
	float AxisVector = Value.Get<float>();
	NextWeapon(AxisVector > 0.f);
}

void UFourTaleWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	UWorld* World = GetWorld();
	if (World)
	{
		if (!WeaponsClasses.IsEmpty())
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = GetOwner();
			for (auto Weapon : WeaponsClasses)
			{
				AFourTaleBaseWeapon* NewWeapon = World->SpawnActor<AFourTaleBaseWeapon>(
					Weapon, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), SpawnParams);
				NewWeapon->SetActorHiddenInGame(true);
				NewWeapon->SetOwner(GetOwner());
				Weapons.Add(NewWeapon);
			}
			CurrentWeapon = Weapons[0];
			CurrentWeapon->SetActorHiddenInGame(false);
		}
		else
		{
			UE_LOG(LogWeaponComponent, Warning, TEXT("%hs Weapons Is Empty"), __FUNCTION__);
		}
	}
}

