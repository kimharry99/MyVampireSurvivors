// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyWaveDataAsset.h"

#include "Enemies/EnemySpawnRecord.h"

UEnemyWaveDataAsset::UEnemyWaveDataAsset(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	WaveType = EWaveType::Enemy;
}

TArray<FEnemySpawnRecord> UEnemyWaveDataAsset::GetSpawningEnemyGroup() const
{
	return SpawningEnemyGroup;
}
