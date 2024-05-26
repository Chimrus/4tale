// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Actors/FourTaleHealthComponent.h"

#include "Actors/Pawns/Characters/FourTaleCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/Actors/Pawns/Characters/FourTaleWeaponComponent.h"
#include "Core/FourTaleGameMode.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY_STATIC(HealthComponentLog, All,All);

UFourTaleHealthComponent::UFourTaleHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}


void UFourTaleHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	SetHealth(MaxHealth);
	ComponentOwner = Cast<AFourTaleCharacter>(GetOwner());
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UFourTaleHealthComponent::OnTakeAnyDamage);
	}
}

void UFourTaleHealthComponent::OnRep_Health()
{
	OnHealthChange.Broadcast(Health, 0);
}

void UFourTaleHealthComponent::SetHealth(float NewHealth)
{
	float OldHealth = Health;
	float NextHealth = FMath::Clamp(NewHealth, 0.f, MaxHealth);
	Health = NextHealth;
	OnHealthChange.Broadcast(Health, OldHealth);
}

void UFourTaleHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Error, TEXT("%hs"), __FUNCTION__)

	SetHealth(Health - Damage);
	if (FMath::IsNearlyZero(Health))
	{
		AFourTaleGameMode* GameMode = Cast<AFourTaleGameMode>(GetWorld()->GetAuthGameMode());
		if (!GameMode)
		{
			return;
		}
		AController* VictimController = ComponentOwner ? ComponentOwner->GetController() : nullptr;
			GameMode->Killed(InstigatedBy, VictimController);	

		UE_LOG(HealthComponentLog, Display, TEXT("Player %s is dead"), *ComponentOwner->GetName());
		ComponentOwner->GetCharacterMovement()->DisableMovement();
		ComponentOwner->GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
		ComponentOwner->WeaponComponent->StopShoot();
		ComponentOwner->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		ComponentOwner->GetMesh()->SetSimulatePhysics(true);
		ComponentOwner->SetLifeSpan(5.f);
	}
}

void UFourTaleHealthComponent::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	DOREPLIFETIME(UFourTaleHealthComponent, Health);
}
