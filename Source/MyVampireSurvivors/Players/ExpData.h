// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExpData.generated.h"

UCLASS()
class MYVAMPIRESURVIVORS_API UExpData : public UObject
{
	GENERATED_BODY()

public:
	void AddExp(int GainedExp);

private:
	UPROPERTY(Transient)
	int CurrentExp = 0;

	UPROPERTY(Transient)
	int CurrentLevel = 1;
};
