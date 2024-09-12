// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyWave.h"
#include "Kismet/GameplayStatics.h"
#include "EnemySpawnRecord.h"
#include "ToroidalMapManager.h"

UEnemyWave* UEnemyWave::CreateEnemyWave(const UWaveDataAsset* WaveDataAsset, UEnemySpawner* EnemySpawner)
{
	const UEnemyWaveDataAsset* EnemyWaveDataAsset = Cast<UEnemyWaveDataAsset>(WaveDataAsset);
	if (EnemyWaveDataAsset == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Wave data asset is not EnemyWaveDataAsset"))
		return nullptr;
	}

	UEnemyWave* EnemyWave = NewObject<UEnemyWave>();
	EnemyWave->EnemyWaveDataAsset = EnemyWaveDataAsset;
	EnemyWave->EnemySpawner = EnemySpawner;
	return EnemyWave;
}

void UEnemyWave::Trigger() const
{
	for (const FEnemySpawnRecord& EnemySpawnRecord : EnemyWaveDataAsset->GetSpawningEnemyGroup())
	{
		EnemySpawner->SpawnEnemies(EnemySpawnRecord.EnemyClass, EnemySpawnRecord.EnemyCount);
	}
}
