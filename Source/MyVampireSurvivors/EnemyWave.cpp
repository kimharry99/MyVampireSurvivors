// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyWave.h"
#include "Kismet/GameplayStatics.h"
#include "EnemySpawnRecord.h"

void UEnemyWave::Trigger() const
{
	for (const FEnemySpawnRecord& EnemySpawnRecord : EnemyWaveDataAsset->GetSpawningEnemyGroup())
	{
		EnemySpawner->SpawnEnemies(EnemySpawnRecord.EnemyClass, EnemySpawnRecord.EnemyCount);
	}
}
