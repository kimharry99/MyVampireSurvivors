// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthData.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOutOfHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnValueChanged);

UCLASS(DefaultToInstanced)
class MYVAMPIRESURVIVORS_API UHealthData : public UObject
{
	GENERATED_BODY()

private:
	float MaxHealth = 0.0f;
	float CurrentHealth = 0.0f;

public:
	void InitializeHealth(float MaxHealthValue);
	float GetHpRatio() const;

public:
	void TakeDamage(float Damage);

	mutable FOnValueChanged OnHealthChanged;
	mutable FOnOutOfHealth OnOutOfHealth;
};
