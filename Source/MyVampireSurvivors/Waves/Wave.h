// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wave.generated.h"

class AEnemySpawner;
class AWave;
class AWave_Deprecated;
class UWaveDataAsset;
struct FWaveActorsToSpawn;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveCleared, AWave*, ClearedWave);

UCLASS(ClassGroup = "Wave")
class MYVAMPIRESURVIVORS_API AWave : public AActor
{
	GENERATED_BODY()

public:
	AWave(const FObjectInitializer& ObjectInitializer);

public:
	void Trigger(const TArray<FWaveActorsToSpawn>& WaveSpawningActors);

	/** Delegate that is broadcasted when the wave is cleared. */
	FOnWaveCleared OnWaveCleared;

private:
	virtual AEnemySpawner* FindSpawner() const;

	TSet<TWeakObjectPtr<AActor>> SpawnedActors;

	UFUNCTION()
	void HandleSpawnActorDestroyed(AEnemy* Actor);

	void ClearWave();
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveCleared_Deprecated, AWave_Deprecated*, ClearedWave);

UCLASS(Abstract)
class MYVAMPIRESURVIVORS_API AWave_Deprecated : public AActor
{
	GENERATED_BODY()

public:
	virtual void InitWaveData(const UWaveDataAsset* InWaveDataAsset);
	virtual void Trigger();

public:
	/** Delegate that is broadcasted when the wave is cleared. */
	FOnWaveCleared_Deprecated OnWaveCleared;

protected:
	virtual void ClearWave();
};
