// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Actors/Pawns/Characters/FourTaleWeaponComponent.h"

#include "Actors/FourTaleBaseWeapon.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All)


UFourTaleWeaponComponent::UFourTaleWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UFourTaleWeaponComponent::StartShoot()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, *FString::Printf(TEXT("Start Shoot")));
}

void UFourTaleWeaponComponent::ReloadWeapon()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, *FString::Printf(TEXT("Reload")));
}

void UFourTaleWeaponComponent::StopShoot()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, *FString::Printf(TEXT("Stop Shoot")));
}

void UFourTaleWeaponComponent::ChangeWeaponFireMode()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, *FString::Printf(TEXT("Change Weapon Fire Mode")));
	if (!CurrentWeapons)
	{
		UE_LOG(LogWeaponComponent, Warning, TEXT("%hs CurrentWeapons is nullptr"), __FUNCTION__);
		return;
	}
	CurrentWeapons->ChangeWeaponFireMode();
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
			const auto Class = WeaponsClasses[0];
			const auto NewWeapon = World->SpawnActor<AFourTaleBaseWeapon>(Class, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), SpawnParams);
			CurrentWeapons = NewWeapon;
		}
		else
		{
			UE_LOG(LogWeaponComponent, Warning, TEXT("%hs Weapons Is Empty"), __FUNCTION__);
		}
	}
}

