// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FourTalePlayerController.generated.h"

UCLASS()
class FOURTALE_API AFourTalePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AFourTalePlayerController();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UPROPERTY()
	UUserWidget* HUDWidget;
	void Respawn();

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastPlayShotEffects(const FVector& TraceStart, const FVector& TraceEnd);
	
	UFUNCTION(Server, Reliable)
	void ServerMakeShot(const FVector& TraceStart, const FVector& TraceEnd, float Damage);

	virtual void OnUnPossess() override;
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION(Client,Reliable)
	void CreateHUD();
};
