// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Enemy.h"
#include "ToroidalMapManager.h"

void UEnemySpawner::SpawnEnemyWave(const FEnemyWaveInfo& EnemyWaveInfo)
{
	// Spawn enemies set in the enemy wave info
	for(const FEnemySpawnInfo& EnemySpawnInfo : EnemyWaveInfo.EnemySpawnInfos)
	{
		SpawnEnemies(EnemySpawnInfo);
	}
}

void UEnemySpawner::SpawnEnemies(const FEnemySpawnInfo& EnemySpawnInfo)
{
	UWorld* World = GetWorld();
	if (World == nullptr) return;

	for (int i = 0; i < EnemySpawnInfo.Count; ++i)
	{
		// Set spawn location
		const FBox& SpawnBoundary = ToroidalMapManager::GetInstance()->GetMapRange();
		FVector SpawnLocation = FMath::RandPointInBox(SpawnBoundary);
		SpawnLocation.Z = 50.0f;

		// Spawn an enemy
		AEnemy* Enemy = World->SpawnActor<AEnemy>(EnemySpawnInfo.EnemyClass, SpawnLocation, FRotator::ZeroRotator);
	}
}
