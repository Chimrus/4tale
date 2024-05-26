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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
