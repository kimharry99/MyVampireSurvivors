// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExpData.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExpChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelUp);

UCLASS()
class MYVAMPIRESURVIVORS_API UExpData : public UObject
{
	GENERATED_BODY()

public:
	void Initialize();

	float GetExpRatio() const;
	int GetMaxExp() const;

	void AddExp(int GainedExp);

public:
	mutable FOnExpChanged OnExpChanged;
	mutable	FOnLevelUp OnLevelUp;

private:
	UPROPERTY(Transient)
	int CurrentExp = 0;

	UPROPERTY(Transient)
	int CurrentMaxExp = 1;

	UPROPERTY(Transient)
	int CurrentLevel = 1;

private:
	void LevelUp();
	void UpdateMaxExp();
};
