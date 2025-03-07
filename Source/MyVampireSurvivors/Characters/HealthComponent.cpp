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
	HealthData->OnOutOfHealth.AddDynamic(this, &ThisClass::HandleOutOfHealth);
	HealthData->OnOutOfHealth.AddDynamic(this, &ThisClass::HandleHealthChanged);
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	HealthData->InitializeHealth(DefaultMaxHealth);
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

void UHealthComponent::HandleHealthChanged()
{
	OnHealthChanged.Broadcast();
}
