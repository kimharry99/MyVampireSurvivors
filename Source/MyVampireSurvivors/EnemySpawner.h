// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enemy.h"
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
	 * Spawn enemies at random locations in map.
	 * 
	 * @param EnemyClass - Enemy class to spawn
	 * @param EnemyCount - Number of enemies to spawn
	 */
	void SpawnEnemies(TSubclassOf<AEnemy> EnemyClass, int EnemyCount) const;
};
