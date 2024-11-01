// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthData.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOutOfHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthChanged);

UCLASS()
class MYVAMPIRESURVIVORS_API UHealthData : public UObject
{
	GENERATED_BODY()

public:
	float GetHpRatio() const;

	void InitializeHealth(float MaxHealthValue);
	void TakeDamage(float Damage);

	FOnHealthChanged OnHealthChanged;
	FOnOutOfHealth OnOutOfHealth;

private:
	float MaxHealth = 0.0f;
	float CurrentHealth = 0.0f;
};
