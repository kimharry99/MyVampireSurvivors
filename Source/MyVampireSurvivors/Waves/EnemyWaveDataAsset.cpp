// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyWaveDataAsset.h"

UEnemyWaveDataAsset::UEnemyWaveDataAsset()
{
	Super::WaveType = EWaveType::Enemy;
}

const TArray<FEnemySpawnRecord>& UEnemyWaveDataAsset::GetSpawningEnemyGroup() const
{
	return SpawningEnemyGroup;
}
