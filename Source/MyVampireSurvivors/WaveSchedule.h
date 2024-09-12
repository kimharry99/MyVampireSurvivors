// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Wave.h"

/**
 * Wave container for scheduling waves.
 * Can only add waves to the schedule.
 */
class MYVAMPIRESURVIVORS_API FWaveSchedule
{
public:
	/**
	 * Add a wave to the schedule.
	 */
	void Add(const UWave& Wave);

	/**
	 * Get current wave in the schedule.
	 * 
	 * @return The current wave in the schedule, or nullptr if there are no more waves.
	 */
	const UWave* GetCurrentWave() const;

	/**
	 * Move to the next wave in the schedule.
	 */
	void StepForward();

private:
	UPROPERTY()
	TArray<TObjectPtr<const UWave>> ScheduledWaves;

	int CurrentWaveIndex = 0;
};
