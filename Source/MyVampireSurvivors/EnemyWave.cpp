// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyWave.h"
#include "EnemySpawnRecord.h"

void UEnemyWave::Trigger()
{
	RemainEnemiesCount = 0;
	for (const FEnemySpawnRecord& EnemySpawnRecord : EnemyWaveDataAsset->GetSpawningEnemyGroup())
	{
		for (int i = 0; i < EnemySpawnRecord.EnemyCount; ++i)
		{
			AEnemy* SpawnedEnemy = EnemySpawner->SpawnEnemy(EnemySpawnRecord.EnemyClass);
			SpawnedEnemy->OnEnemyDied.AddDynamic(this, &ThisClass::PostSpawnedEnemyDie);

			SpawnedEnemies.Add(SpawnedEnemy);
			RemainEnemiesCount++;
		}
	}
}

void UEnemyWave::BeginDestroy()
{
	Super::BeginDestroy();

	for (AEnemy* SpawnedEnemy : SpawnedEnemies)
	{
		if (SpawnedEnemy)
		{
			SpawnedEnemy->OnEnemyDied.RemoveAll(this);
		}
	}
}

void UEnemyWave::PostSpawnedEnemyDie()
{
	RemainEnemiesCount--;
	check(RemainEnemiesCount >= 0);
	if (RemainEnemiesCount == 0)
	{
		ClearWave();
	}
}
