// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/HealthData.h"

float UHealthData::GetHpRatio() const
{
	return CurrentHealth / MaxHealth;
}

void UHealthData::InitializeHealth(float MaxHealthValue)
{
	MaxHealth = MaxHealthValue;
	CurrentHealth = MaxHealth;

	OnHealthChanged.Broadcast();
}

void UHealthData::TakeDamage(float Damage)
{
	CurrentHealth -= Damage;
	OnHealthChanged.Broadcast();

	if(CurrentHealth <= 0)
	{
		OnOutOfHealth.Broadcast();
	}
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);
}
