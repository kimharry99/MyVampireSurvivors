// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/HealthComponent.h"
#include "Players/HealthData.h"
#include "Players/MyVamSurPlayerState.h"

class APlayerController;
class APawn;

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
}

void UHealthComponent::Initialize()
{
	APawn* OwnerPawn = GetPawn<APawn>();
	check(OwnerPawn);

	// Check if the owner pawn is a npc
	if (APlayerController* PlayerController = OwnerPawn->GetController<APlayerController>())
	{
		if (AMyVamSurPlayerState* PlayerState = PlayerController->GetPlayerState<AMyVamSurPlayerState>())
		{
			HealthData = PlayerState->GetHealthData();
		}
	}
	else
	{
		HealthData = NewObject<UHealthData>(this);
	}

	check(HealthData);
	HealthData->InitializeHealth(DefaultMaxHealth);
	HealthData->OnOutOfHealth.AddDynamic(this, &UHealthComponent::HandleOutOfHealth);
}

void UHealthComponent::TakeDamage(float Damage)
{
	if (HealthData)
	{
		HealthData->TakeDamage(Damage);
	}
}

void UHealthComponent::HandleOutOfHealth()
{
	OnDeathStarted.Broadcast();
}
