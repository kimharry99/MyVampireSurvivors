// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/HealthComponent.h"
#include "Characters/HealthData.h"
#include "Players/MyVamSurPlayerState.h"

class APlayerController;
class APawn;

void UHealthComponent::OnRegister()
{
	Super::OnRegister();

	HealthData = NewObject<UHealthData>(this);
	check(HealthData);

	HealthData->InitializeHealth(DefaultMaxHealth);
	HealthData->OnOutOfHealth.AddDynamic(this, &UHealthComponent::HandleOutOfHealth);
}

void UHealthComponent::OnUnregister()
{
	if (HealthData)
	{
		HealthData->OnOutOfHealth.RemoveDynamic(this, &UHealthComponent::HandleOutOfHealth);
	}

	Super::OnUnregister();
}

const UHealthData* UHealthComponent::GetHealthData() const
{
	return HealthData;
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
