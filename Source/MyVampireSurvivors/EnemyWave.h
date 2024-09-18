// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Wave.h"
#include "WaveFactory.h"
#include "EnemyWaveDataAsset.h"
#include "EnemySpawner.h"
#include "EnemyWave.generated.h"

/**
 * 
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UEnemyWave : public UWave
{
	GENERATED_BODY()

protected:
	/**
	 * Trigger the wave.
	 *
	 * Spawn enemies based on enemy wave data asset.
	 */
	virtual void Trigger() override;

private:
	friend UWaveFactory;

	/** Enemy wave data asset */
	UPROPERTY()
	TObjectPtr<const UEnemyWaveDataAsset> EnemyWaveDataAsset;

	/** Enemy spawner to spawn enemies */
	UPROPERTY()
	TObjectPtr<AEnemySpawner> EnemySpawner;

	/** The number of remain enemies spawned by the enemy wave. */
	int RemainEnemiesCount = 0;

	/**
	 * Post spawned enemy death event handler.
	 */
	void PostSpawnedEnemyDie();

	/**
	 * Complete the enemy wave.
	 */
	void CompleteEnemyWave();
};
