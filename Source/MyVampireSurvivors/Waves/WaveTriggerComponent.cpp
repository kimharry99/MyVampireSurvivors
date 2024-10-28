// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveTriggerComponent.h"
#include "Waves/Wave.h"
#include "Waves/WaveList.h"

UWaveTriggerComponent::UWaveTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWaveTriggerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(WaveHandle);
	}
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

int UWaveTriggerComponent::GetCurrentWaveIndex() const
{
	return CurrentWaveIndex;
}

float UWaveTriggerComponent::GetTimeUntilNextWave() const
{
	if (UWorld* World = GetWorld())
	{
		return World->GetTimerManager().GetTimerRemaining(WaveHandle);
	}
	return -1.0f;
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

void UWaveTriggerComponent::StepToNextWave()
{
	CurrentWaveIndex++;
}

void UWaveTriggerComponent::TriggerNextWave()
{
	StepToNextWave();
	TriggerCurrentWave();
}

void UWaveTriggerComponent::PostCurrentWaveTriggerd()
{
	ReserveNextWave();
}

void UWaveTriggerComponent::ReserveNextWave()
{
	if (UWorld* World = GetWorld())
	{
		// Set a timer to trigger the next wave
		World->GetTimerManager().ClearTimer(WaveHandle);
		World->GetTimerManager().SetTimer(WaveHandle, this, &UWaveTriggerComponent::TriggerNextWave, WavePeriod, false);
	}
}
