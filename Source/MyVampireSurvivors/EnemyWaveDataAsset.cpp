// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyWaveDataAsset.h"

const TArray<FEnemySpawnRecord>& UEnemyWaveDataAsset::GetSpawningEnemyGroup() const
{
	return SpawningEnemyGroup;
}
