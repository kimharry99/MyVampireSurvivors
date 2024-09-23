// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveList.h"

void UWaveList::Add(UWave* NewWave)
{
	NewWave->OnWaveCleared.AddDynamic(this, &ThisClass::HandleWaveCleared);
	
	Waves.Add(NewWave);
	RemainWavesCount++;
}

UWave* UWaveList::GetWave(int Index) const
{
	if (Waves.IsValidIndex(Index))
	{
		return Waves[Index];
	}
	return nullptr;
}

void UWaveList::BeginDestroy()
{
	Super::BeginDestroy();

	for (UWave* Wave : Waves)
	{
		Wave->OnWaveCleared.RemoveAll(this);
	}
}

void UWaveList::HandleWaveCleared()
{
	RemainWavesCount--;

	check(RemainWavesCount >= 0);
	if (RemainWavesCount == 0)
	{
		OnAllWavesCleared.Broadcast();
	}
}
