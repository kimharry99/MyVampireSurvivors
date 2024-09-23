// Fill out your copyright notice in the Description page of Project Settings.


#include "Wave.h"

void UWave::Trigger()
{

}

void UWave::ClearWave()
{
	UE_LOG(LogTemp, Warning, TEXT("Wave Cleared: %s"), *GetName());
	OnWaveCleared.Broadcast();
	PostWaveCleared();
}

void UWave::PostWaveCleared()
{

}
