// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveFactory.h"

#include "MyVamSurLogChannels.h"
#include "Waves/EnemyWave.h"
#include "Waves/WaveDataAsset.h"

AWave_Deprecated* FWaveFactory::CreateWave(const UWaveDataAsset* WaveDataAsset, AActor* WaveOwner)
{
	check(WaveDataAsset);
	check(WaveOwner);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = WaveOwner;
	SpawnParams.Instigator = WaveOwner->GetInstigator();

	if (UWorld* World = WaveOwner->GetWorld())
	{
		switch (WaveDataAsset->WaveType)
		{
		case EWaveType::Enemy:
			if (AWave_Deprecated* Wave = World->SpawnActor<AEnemyWave>(AEnemyWave::StaticClass(), SpawnParams))
			{
				Wave->InitWaveData(WaveDataAsset);
				return Wave;
			}
		default:
			UE_LOG(LogMyVamSur, Warning, TEXT("Unknown wave type"));
			break;
		}
	}
	else
	{
		UE_LOG(LogMyVamSur, Error, TEXT("FWaveFactory::CreateWave - Failed to get World from WaveOwner: %s."), *GetPathNameSafe(WaveOwner));
	}

	return nullptr;
}
