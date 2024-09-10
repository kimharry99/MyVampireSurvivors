// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "ToroidalMapManager.h"

void UEnemySpawner::SpawnEnemies(TSubclassOf<AEnemy> EnemyClass, int EnemyCount) const
{
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		const FBox& SpawnBoundary = ToroidalMapManager::GetInstance()->GetMapRange();
		for (int i = 0; i < EnemyCount; ++i)
		{
			// Set spawn location
			FVector SpawnLocation = FMath::RandPointInBox(SpawnBoundary);
			SpawnLocation.Z = 50.0f;

			// Spawn an enemy
			AEnemy* Enemy = World->SpawnActor<AEnemy>(EnemyClass, SpawnLocation, FRotator::ZeroRotator);
		}
	}
}
