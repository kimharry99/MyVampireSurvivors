// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveManager.generated.h"

class AWave;
class UWaveDataAsset;
class UWaveFactory;
class UWaveScheduleData;

/**
 * WaveManager_Deprecated handles ordered waves.
 *
 * It triggers an initial wave when the game starts.
 * After a cooldown period in the wave has passed, the class will trigger the next wave.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API AWaveManager : public AActor
{
	GENERATED_BODY()

protected:
	//~AActor Interface
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~End of AActor Interface

public:
	int GetCurrentWaveNumber() const;
	float GetTimeUntilNextWave() const;

private:
	UPROPERTY()
	TObjectPtr<UWaveFactory> WaveFactory;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	TObjectPtr<const UWaveScheduleData> WaveSchedule;

	UPROPERTY(Transient)
	float WavePeriod;

	int CurrentWaveIndex = -1;

	UPROPERTY()
	TObjectPtr<const UWaveDataAsset> UpcomingWaveData = nullptr;

	UPROPERTY()
	TArray<TObjectPtr<AWave>> TriggeredWaves;

	FTimerHandle WavePeriodTimerHandle;

private:
	bool IsAllWavesTriggered() const;

private:
	void TriggerUpcomingWave();
	void UpdateUpcomingWaveData();
	void SetPeriodTimer();

	UFUNCTION()
	void PostPeriodTimerComplete();

private:
	UFUNCTION()
	void HandleWaveClear(AWave* ClearedWave);

	void HandleAllWavesCleared();
};
