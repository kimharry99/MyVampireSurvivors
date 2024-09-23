// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemies/EnemySpawner.h"
#include "Wave.h"
#include "WaveFactory.h"
#include "EnemyWaveDataAsset.h"
#include "EnemyWave.generated.h"

/**
 * 
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UEnemyWave : public UWave
{
	GENERATED_BODY()

protected:
	//~UWave interface
	/** Spawn enemies based on enemy wave data asset. */
	virtual void Trigger() override;
	//~End of UWave interface
	
	//~UObject interface
	virtual void BeginDestroy() override;
	//~End of UObject interface

private:
	friend UWaveFactory;

	/** Enemy wave data asset */
	UPROPERTY()
	TObjectPtr<const UEnemyWaveDataAsset> EnemyWaveDataAsset;

	/** Enemy spawner to spawn enemies */
	UPROPERTY()
	TObjectPtr<AEnemySpawner> EnemySpawner;

	UPROPERTY()
	TArray<TObjectPtr<AEnemy>> SpawnedEnemies;

	/** The number of remain enemies spawned by the enemy wave. */
	int RemainEnemiesCount = 0;

	/**
	 * Post spawned enemy death event handler.
	 */
	UFUNCTION()
	void PostSpawnedEnemyDie();
};
