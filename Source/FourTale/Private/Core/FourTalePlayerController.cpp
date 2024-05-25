// Fill out your copyright notice in the Description page of Project Settings.


#include "FourTale/Public/Core/FourTalePlayerController.h"


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
	
}

// Called every frame
void AFourTalePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

