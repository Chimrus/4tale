// Fill out your copyright notice in the Description page of Project Settings.


#include "FourTale/Public/Core/FourTalePlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Character.h"

DEFINE_LOG_CATEGORY_STATIC(PlayerControlleLog, All, All);

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

void AFourTalePlayerController::ServerMakeShot_Implementation(const FVector& TraceStart, const FVector& TraceEnd, float Damage)
{
	ACharacter* LCharacter = Cast<ACharacter>(GetPawn());
	if (!LCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("%hs Player not valid"), __FUNCTION__)
		return;
	}
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(LCharacter);

	if (GetWorld()->LineTraceSingleByProfile(HitResult, TraceStart, TraceEnd, EName::Pawn, QueryParams))
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			FPointDamageEvent DamageEvent(Damage, HitResult, (TraceEnd - TraceStart).GetSafeNormal(), nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, this, LCharacter);
		}
	}

	MulticastPlayShotEffects(TraceStart, TraceEnd);
}

void AFourTalePlayerController::MulticastPlayShotEffects_Implementation(const FVector& TraceStart, const FVector& TraceEnd)
{
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.0f, 0, 1.0f);
}