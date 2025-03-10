// Fill out your copyright notice in the Description page of Project Settings.


#include "Wave.h"

#include "Waves/WaveDataAsset.h"
#include "MyVamSurLogChannels.h"

void AWave_Deprecated::InitWaveData(const UWaveDataAsset* InWaveDataAsset)
{
	// Empty implementation
}

void AWave_Deprecated::Trigger()
{
	// Empty implementation
}

void AWave_Deprecated::ClearWave()
{
	UE_LOG(LogMyVamSur, Warning, TEXT("Wave Cleared: %s"), *GetName());
	OnWaveCleared.Broadcast(this);
	Destroy();
}
