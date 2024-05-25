// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FourTaleHealthComponent.generated.h"
DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChange, float NewHealthValue, float OldHealthValue);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FOURTALE_API UFourTaleHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFourTaleHealthComponent();

	FORCEINLINE float GetHealth() const {return Health;}
	FORCEINLINE float GetMaxHealth() const {return MaxHealth;}
	FORCEINLINE float GetHealthPercent() const {return Health/MaxHealth;}

	UPROPERTY()
	FOnDeath OnDeath;

	UPROPERTY()
	FOnHealthChange	OnHealthChange;

protected:

	
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float MaxHealth = 100.f;

	UPROPERTY(ReplicatedUsing = OnRep_Health)
	float Health;

	UFUNCTION()
	void OnRep_Health();
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetHealth(float NewHealth);

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
							   class AController* InstigatedBy, AActor* DamageCauser);
};
