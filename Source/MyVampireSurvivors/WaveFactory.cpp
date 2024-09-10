// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveFactory.h"
#include "EnemyWave.h"

UWaveFactory::UWaveFactory()
{
	EnemySpawner = CreateDefaultSubobject<UEnemySpawner>(TEXT("EnemySpawner"));
}

UWave* UWaveFactory::CreateWave(const UWaveDataAsset* WaveDataAsset) const
{
	switch (WaveDataAsset->WaveType)
	{
		case EWaveType::Enemy:
			return UEnemyWave::CreateEnemyWave(WaveDataAsset, EnemySpawner);
		break;
		default:
			UE_LOG(LogTemp, Error, TEXT("Unknown wave type"))
			return nullptr;
	}
}
