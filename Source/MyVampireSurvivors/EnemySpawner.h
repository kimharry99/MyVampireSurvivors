// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnemyWaveInfo.h"
#include "EnemySpawnInfo.h"
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
	 * @param EnemyWaveInfo The enemy wave info.
	 */
	void SpawnEnemyWave(const FEnemyWaveInfo& EnemyWaveInfo);

	/**
	 * Spawn enemies according to the enemy spawn info.
	 * 
	 * @param EnemySpawnInfo The enemy spawn info.
	 */
	void SpawnEnemies(const FEnemySpawnInfo& EnemySpawnInfo);
};
