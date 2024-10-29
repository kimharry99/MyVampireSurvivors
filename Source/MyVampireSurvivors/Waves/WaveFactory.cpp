// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveFactory.h"
#include "MyVamSurLogChannels.h"
#include "EnemyWave.h"

AWave* UWaveFactory::CreateWave(const UWaveDataAsset* WaveDataAsset) const
{
	if (WaveDataAsset == nullptr)
	{
		UE_LOG(LogMyVamSur, Error, TEXT("Input WaveDataAsset is nullptr"));
		return nullptr;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Cast<AActor>(GetOuter());
	SpawnParams.Instigator = nullptr;

	if (UWorld* World = GetWorld())
	{
		AWave* Wave = nullptr;
		switch (WaveDataAsset->WaveType)
		{
			case EWaveType::Enemy:
				Wave = World->SpawnActor<AEnemyWave>(AEnemyWave::StaticClass(), SpawnParams);
				Wave->InitWaveData(WaveDataAsset);
				break;
			default:
				UE_LOG(LogMyVamSur, Error, TEXT("Unknown wave type"));
				break;
		}
		return Wave;
	}

	return nullptr;
}
