// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyWave.h"
#include "EnemySpawnRecord.h"

UEnemyWave* UEnemyWave::CreateEnemyWave(const UWaveDataAsset* WaveDataAsset)
{
	const UEnemyWaveDataAsset* EnemyWaveDataAsset = Cast<UEnemyWaveDataAsset>(WaveDataAsset);
	if (EnemyWaveDataAsset == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Wave data asset is not EnemyWaveDataAsset"))
		return nullptr;
	}

	UEnemyWave* EnemyWave = NewObject<UEnemyWave>();
	EnemyWave->EnemyWaveDataAsset = EnemyWaveDataAsset;
	return EnemyWave;
}

void UEnemyWave::Trigger()
{
	// FIXME: Separate enemies spawning logic to a separate class
	for (const FEnemySpawnRecord& EnemySpawnRecord : EnemyWaveDataAsset->GetSpawningEnemyGroup())
	{
		const FString EnemyName = EnemySpawnRecord.EnemyClass->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Spawning enemy: %s"), *EnemyName);
	}
}
