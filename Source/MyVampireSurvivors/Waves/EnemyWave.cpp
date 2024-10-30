// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyWave.h"
#include "Enemies/Enemy.h"
#include "Enemies/EnemySpawner.h"
#include "Enemies/EnemySpawnRecord.h"
#include "GameModes/MyVamSurGameMode.h"
#include "Waves/EnemyWaveDataAsset.h"
#include "Waves/WaveFactory.h"

void AEnemyWave::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	check(World);

	AMyVamSurGameMode* GameMode = World->GetAuthGameMode<AMyVamSurGameMode>();
	check(GameMode);

	EnemySpawner = GameMode->GetEnemySpawner();
}

void AEnemyWave::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for (AEnemy* SpawnedEnemy : SpawnedEnemies)
	{
		if (SpawnedEnemy)
		{
			SpawnedEnemy->OnEnemyDied.RemoveAll(this);
		}
	}

	Super::EndPlay(EndPlayReason);
}

void AEnemyWave::InitWaveData(const UWaveDataAsset* InWaveDataAsset)
{
	if (InWaveDataAsset->IsA(UEnemyWaveDataAsset::StaticClass()))
	{
		EnemyWaveDataAsset = Cast<const UEnemyWaveDataAsset>(InWaveDataAsset);
	}
}

void AEnemyWave::Trigger()
{
	for (const FEnemySpawnRecord& EnemySpawnRecord : EnemyWaveDataAsset->GetSpawningEnemyGroup())
	{
		for (int i = 0; i < EnemySpawnRecord.EnemyCount; ++i)
		{
			AEnemy* SpawnedEnemy = EnemySpawner->SpawnEnemy(EnemySpawnRecord.EnemyClass);
			SpawnedEnemy->OnEnemyDied.AddDynamic(this, &ThisClass::HandleSpawnedEnemyDie);
			SpawnedEnemies.Add(SpawnedEnemy);
		}
	}
}

void AEnemyWave::HandleSpawnedEnemyDie(AEnemy* DiedEnemy)
{
	if (SpawnedEnemies.Contains(DiedEnemy))
	{
		SpawnedEnemies.Remove(DiedEnemy);
	}

	if (SpawnedEnemies.Num() == 0)
	{
		ClearWave();
	}
}
