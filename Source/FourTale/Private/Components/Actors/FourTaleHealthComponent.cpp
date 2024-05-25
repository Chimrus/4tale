// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Actors/FourTaleHealthComponent.h"

#include "Net/UnrealNetwork.h"

UFourTaleHealthComponent::UFourTaleHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicated(true);
}


void UFourTaleHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	SetHealth(MaxHealth);

	if (AActor* ComponentOwner = GetOwner())
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UUECHealthComponent::OnTakeAnyDamage);
	}
}

void UFourTaleHealthComponent::SetHealth(float NewHealth)
{
	float OldHealth = Health;
	float NextHealth = FMath::Clamp(NewHealth, 0.f, MaxHealth);
	Health = NextHealth;
	OnHealthChange.Broadcast(Health, OldHealth);
}

void UFourTaleHealthComponent::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	DOREPLIFETIME(UFourTaleHealthComponent, Health);
}
