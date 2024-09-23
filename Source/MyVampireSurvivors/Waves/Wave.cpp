// Fill out your copyright notice in the Description page of Project Settings.


#include "Wave.h"
#include "MyVamSurLogChannels.h"

void UWave::Trigger()
{

}

void UWave::ClearWave()
{
	UE_LOG(LogMyVamSur, Warning, TEXT("Wave Cleared: %s"), *GetName());
	OnWaveCleared.Broadcast();
	PostWaveCleared();
}

void UWave::PostWaveCleared()
{

}
