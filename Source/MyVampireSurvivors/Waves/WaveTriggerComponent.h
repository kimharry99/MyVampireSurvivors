// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WaveTriggerComponent.generated.h"

class AWave_Deprecated;
class UWaveDataAsset;
class UWaveScheduleData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveTriggered, AWave_Deprecated*, TriggeredWave);

/**
 * WaveTriggerComponent is responsible for executing wave schedules, triggering waves at specified intervals,
 * and notifying other components when a wave starts.
 */
UCLASS(ClassGroup = Wave)
class MYVAMPIRESURVIVORS_API UWaveTriggerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWaveTriggerComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	/**
	 * Sets the wave schedule data that defines the wave sequence and period.
	 * 
	 * @param NewWaveScheduleData The new wave schedule to be applied.
	 */
	void SetWaveSchedule(const UWaveScheduleData* NewWaveScheduleData);

	void BeginWaveSchedule();

	int GetCurrentWaveIndex() const;
	float GetTimeUntilNextWave() const;

	bool IsWaveScheduleDone() const;

	FOnWaveTriggered OnWaveTriggered;

private:
	UPROPERTY(Transient)
	TArray<TObjectPtr<const UWaveDataAsset>> WaveSequence;

	UPROPERTY(Transient)
	float WavePeriod;

	UPROPERTY(Transient)
	int UpcomingWaveIndex;

	FTimerHandle WavePeriodTimerHandle;

	void TriggerUpcomingWave();

	void SetPeriodTimer();

	void OnPeriodTimerCompleted();
};
