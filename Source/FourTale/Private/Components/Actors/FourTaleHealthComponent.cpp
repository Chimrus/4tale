// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Actors/FourTaleHealthComponent.h"

UFourTaleHealthComponent::UFourTaleHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UFourTaleHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UFourTaleHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

