// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wave.generated.h"

class AEnemySpawner;
class AWave_Deprecated;
class UWaveDataAsset;
struct FWaveActorsToSpawn;

UCLASS(ClassGroup = "Wave")
class MYVAMPIRESURVIVORS_API AWave : public AActor
{
	GENERATED_BODY()

public:
	AWave(const FObjectInitializer& ObjectInitializer);

public:
	void Trigger(const TArray<FWaveActorsToSpawn>& WaveSpawningActors);

private:
	virtual AEnemySpawner* FindSpawner() const;

	TArray<TWeakObjectPtr<AActor>> SpawnedActors;
};

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
