// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveTriggerComponent.h"

UWaveTriggerComponent::UWaveTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWaveTriggerComponent::StartWave()
{
	CurrentWaveIndex = 0;
	TriggerCurrentWave();
}

void UWaveTriggerComponent::SetWaveList(UWaveList* InWaveList)
{
	WaveList = InWaveList;
}

void UWaveTriggerComponent::TriggerCurrentWave()
{
	UWave* CurrentWave = WaveList->GetWave(CurrentWaveIndex);

	// If the index is out of bounds, stop triggering waves
	if (CurrentWave)
	{
		CurrentWave->Trigger();
		PostCurrentWaveTriggerd();
	}
}

void UWaveTriggerComponent::PostCurrentWaveTriggerd()
{
	ReserveNextWave();
}

void UWaveTriggerComponent::ReserveNextWave()
{
	// Increment wave index in the schedule
	CurrentWaveIndex++;

	// Set a timer to trigger the next wave
	UWorld* World = GetWorld();

	check(World);
	World->GetTimerManager().ClearTimer(WaveHandle);
	World->GetTimerManager().SetTimer(WaveHandle, this, &UWaveTriggerComponent::TriggerCurrentWave, WavePeriod, false);
}
