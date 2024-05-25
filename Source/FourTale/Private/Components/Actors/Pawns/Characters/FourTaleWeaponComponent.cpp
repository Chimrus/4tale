// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Actors/Pawns/Characters/FourTaleWeaponComponent.h"


// Sets default values for this component's properties
UFourTaleWeaponComponent::UFourTaleWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
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


// Called when the game starts
void UFourTaleWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFourTaleWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

