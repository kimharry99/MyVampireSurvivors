// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/HealthData.h"

void UHealthData::InitializeHealth(float MaxHealthValue)
{
	MaxHealth = MaxHealthValue;
	CurrentHealth = MaxHealth;
}

void UHealthData::TakeDamage(float Damage)
{
	CurrentHealth -= Damage;
	if(CurrentHealth <= 0)
	{
		OnOutOfHealth.Broadcast();
	}
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);
}
