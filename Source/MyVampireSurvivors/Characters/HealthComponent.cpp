// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/HealthComponent.h"
#include "Characters/HealthData.h"
#include "Players/MyVamSurPlayerState.h"

class APlayerController;
class APawn;

UHealthComponent::UHealthComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	HealthData = CreateDefaultSubobject<UHealthData>(TEXT("HealthData"));
	HealthData->InitializeHealth(DefaultMaxHealth);
	HealthData->OnOutOfHealth.AddDynamic(this, &ThisClass::HandleOutOfHealth);
}

const UHealthData* UHealthComponent::GetHealthData() const
{
	return HealthData;
}

float UHealthComponent::GetHPRatio() const
{
	return HealthData->GetHpRatio();
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
