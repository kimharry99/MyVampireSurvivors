// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WaveTriggerComponent.generated.h"

class AWave;
class UWaveDataAsset;
class UWaveFactory;
class UWaveScheduleData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveTriggered, AWave*, TriggeredWave);

UCLASS(ClassGroup = Wave)
class MYVAMPIRESURVIVORS_API UWaveTriggerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWaveTriggerComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	void SetWaveSchedule(const UWaveScheduleData* NewWaveScheduleData);

	void BeginWaveSchedule();

	int GetCurrentWaveIndex() const;
	float GetTimeUntilNextWave() const;

	bool IsAllWavesTriggered() const;

	FOnWaveTriggered OnWaveTriggered;

private:
	UPROPERTY(Instanced)
	TObjectPtr<UWaveFactory> WaveFactory;

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
