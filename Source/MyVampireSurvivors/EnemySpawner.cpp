// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Enemy.h"
#include "ToroidalMapManager.h"

void UEnemySpawner::SpawnEnemyWave(const UEnemyWaveDataAsset* EnemyWaveRecord)
{
	const TArray<FEnemySpawnRecord>& SpawningEnemyGroup = EnemyWaveRecord->GetSpawningEnemyGroup();
	// Spawn enemies set in the enemy wave info
	for(const FEnemySpawnRecord& EnemySpawnInfo : SpawningEnemyGroup)
	{
		SpawnEnemies(EnemySpawnInfo);
	}
}

void UEnemySpawner::SpawnEnemies(const FEnemySpawnRecord& EnemySpawnRecord)
{
	UWorld* World = GetWorld();
	if (World == nullptr) return;

	for (int i = 0; i < EnemySpawnRecord.EnemyCount; ++i)
	{
		// Set spawn location
		const FBox& SpawnBoundary = ToroidalMapManager::GetInstance()->GetMapRange();
		FVector SpawnLocation = FMath::RandPointInBox(SpawnBoundary);
		SpawnLocation.Z = 50.0f;

		// Spawn an enemy
		AEnemy* Enemy = World->SpawnActor<AEnemy>(EnemySpawnRecord.EnemyClass, SpawnLocation, FRotator::ZeroRotator);
	}
}
