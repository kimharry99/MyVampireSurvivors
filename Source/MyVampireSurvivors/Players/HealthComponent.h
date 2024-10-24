// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class UHealthData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathStarted);

UCLASS()
class MYVAMPIRESURVIVORS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void TakeDamage(float Damage);

	FOnDeathStarted OnDeathStarted;

protected:
	//~UActorComponent interface
	virtual void BeginPlay() override;
	//~End of UActorComponent interface

private:
	void Initialize();

	UFUNCTION()
	void HandleOutOfHealth();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Data")
	float DefaultMaxHealth = 0.0f;

	UPROPERTY()
	TObjectPtr<UHealthData> HealthData;

	template <typename T>
	T* GetPawn() const
	{
		return Cast<T>(GetOwner());
	}
};
