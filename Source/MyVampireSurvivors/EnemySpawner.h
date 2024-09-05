// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnemyWaveDataAsset.h"
#include "EnemySpawnRecord.h"
#include "EnemySpawner.generated.h"

/**
 * EnemySpanwer spawns enemies at random locations.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UEnemySpawner : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * Spawn an enemy wave according to the enemy wave info.
	 *
	 * @param EnemyWaveRecord The enemy wave info.
	 */
	void SpawnEnemyWave(const UEnemyWaveDataAsset* EnemyWaveRecord);

	/**
	 * Spawn enemies according to the enemy spawn data.
	 * 
	 * @param EnemySpawnRecord The enemy spawn data.
	 */
	void SpawnEnemies(const FEnemySpawnRecord& EnemySpawnRecord);
};
