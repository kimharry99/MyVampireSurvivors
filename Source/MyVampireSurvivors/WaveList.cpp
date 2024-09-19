// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveList.h"

void UWaveList::Add(UWave* NewWave)
{
	Waves.Add(NewWave);
}

UWave* UWaveList::GetWave(int Index) const
{
	if (Waves.IsValidIndex(Index))
	{
		return Waves[Index];
	}
	return nullptr;
}
