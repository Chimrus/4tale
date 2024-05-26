// Fill out your copyright notice in the Description page of Project Settings.


#include "FourTale/Public/Core/FourTalePlayerController.h"

#include "Blueprint/UserWidget.h"

DEFINE_LOG_CATEGORY_STATIC(PlayerControlleLog, All,All);

// Sets default values
AFourTalePlayerController::AFourTalePlayerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFourTalePlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (HUDWidgetClass)
	{
		UUserWidget* HUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		HUDWidget->AddToViewport();
	}
	else
	{
		UE_LOG(PlayerControlleLog, Error, TEXT("%hs HUDWidgetClass is empty!"), __FUNCTION__);
	}
}

// Called every frame
void AFourTalePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
