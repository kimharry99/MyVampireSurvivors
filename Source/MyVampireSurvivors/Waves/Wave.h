// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wave.generated.h"

class AWave_Deprecated;
class UWaveDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveCleared, AWave_Deprecated*, ClearedWave);

UCLASS(Abstract)
class MYVAMPIRESURVIVORS_API AWave_Deprecated : public AActor
{
	GENERATED_BODY()

public:
	virtual void InitWaveData(const UWaveDataAsset* InWaveDataAsset);
	virtual void Trigger();

public:
	/** Delegate that is broadcasted when the wave is cleared. */
	FOnWaveCleared OnWaveCleared;

protected:
	virtual void ClearWave();
};
