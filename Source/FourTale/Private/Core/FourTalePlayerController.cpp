// Fill out your copyright notice in the Description page of Project Settings.


#include "FourTale/Public/Core/FourTalePlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Core/FourTaleGameMode.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Character.h"

DEFINE_LOG_CATEGORY_STATIC(PlayerControlleLog, All, All);

// Sets default values
AFourTalePlayerController::AFourTalePlayerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AFourTalePlayerController::Respawn()
{
	AFourTaleGameMode* GameMode = Cast<AFourTaleGameMode>(GetWorld()->GetAuthGameMode());
	if (!GameMode)
	{
		return;
	}
	GameMode->RestartPlayer(this);
}

void AFourTalePlayerController::OnUnPossess()
{
	Super::OnUnPossess();
	if (HUDWidget)
	{
		HUDWidget->RemoveFromParent();
	}

	FTimerHandle RespawnTimerHandle;
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &AFourTalePlayerController::Respawn, 5, false);
}

void AFourTalePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	FTimerHandle HUDTimer;
	GetWorldTimerManager().SetTimer(HUDTimer, this, &AFourTalePlayerController::CreateHUD, 1, false);
}

void AFourTalePlayerController::CreateHUD_Implementation()
{
	if (HUDWidgetClass)
	{
		HUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		HUDWidget->AddToViewport();
	}
	else
	{
		UE_LOG(PlayerControlleLog, Error, TEXT("%hs HUDWidgetClass is empty!"), __FUNCTION__);
	}
}

void AFourTalePlayerController::ServerMakeShot_Implementation(const FVector& TraceStart, const FVector& TraceEnd,
                                                              float Damage)
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

void AFourTalePlayerController::MulticastPlayShotEffects_Implementation(const FVector& TraceStart,
                                                                        const FVector& TraceEnd)
{
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.0f, 0, 1.0f);
}
