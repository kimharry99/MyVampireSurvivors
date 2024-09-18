// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveTriggerComponent.h"

UWaveTriggerComponent::UWaveTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWaveTriggerComponent::StartWave()
{
	TriggerCurrentWave();
}

FWaveSchedule& UWaveTriggerComponent::GetWaveSchedule()
{
	return WaveSchedule;
}

void UWaveTriggerComponent::TriggerCurrentWave()
{
	UWave* CurrentWave = WaveSchedule.GetCurrentWave();
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
	WaveSchedule.StepForward();

	// Set a timer to trigger the next wave
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().ClearTimer(WaveHandle);
		World->GetTimerManager().SetTimer(WaveHandle, this, &UWaveTriggerComponent::TriggerCurrentWave, WavePeriod, false);
	}
}
