// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "EnemySpawnRecord.generated.h"

/**
 * A structure for representing enemy spawning event.
 */
USTRUCT(BlueprintType)
struct MYVAMPIRESURVIVORS_API FEnemySpawnRecord
{
	GENERATED_BODY()

	/**
	 * Number of enemies to spawn.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Spawning")
	int EnemyCount;

	/**
	 * Class of the enemy to spawn.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<AEnemy> EnemyClass;
};