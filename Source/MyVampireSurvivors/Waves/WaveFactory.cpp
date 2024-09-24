// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveFactory.h"
#include "MyVamSurLogChannels.h"
#include "EnemyWave.h"

void UWaveFactory::SetEnemySpawner(AEnemySpawner* InEnemySpawner)
{
	EnemySpawner = InEnemySpawner;
}

UWave* UWaveFactory::CreateWave(const UWaveDataAsset* WaveDataAsset) const
{
	switch (WaveDataAsset->WaveType)
	{
		case EWaveType::Enemy:
		{
			UEnemyWave* EnemyWave = NewObject<UEnemyWave>();
			EnemyWave->EnemyWaveDataAsset = Cast<UEnemyWaveDataAsset>(WaveDataAsset);
			EnemyWave->EnemySpawner = EnemySpawner;
			return EnemyWave;
		}
		default:
		{
			UE_LOG(LogMyVamSur, Error, TEXT("Unknown wave type"));
			return nullptr;
		}
	}
}
