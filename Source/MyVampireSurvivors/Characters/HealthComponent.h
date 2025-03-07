// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class UHealthData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthChanged);

UCLASS()
class MYVAMPIRESURVIVORS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	//~UActorComponent interface
	virtual void OnRegister() override;
	virtual void OnUnregister() override;
	//~End of UActorComponent interface

private:
	template <typename T>
	T* GetPawn() const
	{
		return Cast<T>(GetOwner());
	}

private:
	UPROPERTY(EditDefaultsOnly, Category = "Data")
	float DefaultMaxHealth = 0.0f;

	UPROPERTY()
	TObjectPtr<UHealthData> HealthData;

public:
	const UHealthData* GetHealthData() const;

public:
	float GetHPRatio() const;

	void TakeDamage(float Damage);

	FOnDeathStarted OnDeathStarted;
	FOnHealthChanged OnHealthChanged;

private:
	UFUNCTION()
	void HandleOutOfHealth();
};
