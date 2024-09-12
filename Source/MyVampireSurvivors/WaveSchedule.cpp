// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveSchedule.h"

void FWaveSchedule::Add(const UWave& Wave)
{
	ScheduledWaves.Add(&Wave);
}

const UWave* FWaveSchedule::GetCurrentWave() const
{
	if (CurrentWaveIndex >= ScheduledWaves.Num())
	{
		return nullptr;
	}

	return ScheduledWaves[CurrentWaveIndex];
}

void FWaveSchedule::StepForward()
{
	++CurrentWaveIndex;
}
