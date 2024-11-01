// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExpData.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExpChanged);

UCLASS()
class MYVAMPIRESURVIVORS_API UExpData : public UObject
{
	GENERATED_BODY()

public:
	void AddExp(int GainedExp);
	float GetExpRatio() const;
	
	FOnExpChanged OnExpChanged;

private:
	UPROPERTY(Transient)
	int CurrentExp = 0;

	int MaxExp = 100;

	UPROPERTY(Transient)
	int CurrentLevel = 1;
};
