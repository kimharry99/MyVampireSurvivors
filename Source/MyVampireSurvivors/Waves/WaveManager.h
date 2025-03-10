// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveManager.generated.h"

class AWave;
class UWaveDataAsset;
class UWaveFactory;
class UWaveScheduleData;
class UWaveTriggerComponent;

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

public:
	AWaveManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

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
	UPROPERTY(VisibleAnywhere, Category = "Wave")
	TObjectPtr<UWaveTriggerComponent> WaveTriggerComponent;

	UPROPERTY()
	TObjectPtr<UWaveFactory> WaveFactory;

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	TObjectPtr<const UWaveScheduleData> WaveSchedule;

	UPROPERTY(Transient)
	float WavePeriod;

	UPROPERTY(Transient)
	int CurrentWaveIndex = -1;

	UPROPERTY()
	TObjectPtr<const UWaveDataAsset> UpcomingWaveData = nullptr;

	UPROPERTY()
	TArray<TObjectPtr<AWave>> TriggeredWaves;

	FTimerHandle WavePeriodTimerHandle;

	bool IsAllWavesTriggered() const;

	void TriggerUpcomingWave();
	void UpdateUpcomingWaveData();
	void SetPeriodTimer();

	UFUNCTION()
	void PostPeriodTimerComplete();

	UFUNCTION()
	void HandleWaveTriggered(AWave* Wave);

	UFUNCTION()
	void HandleWaveClear(AWave* ClearedWave);

	void HandleAllWavesCleared();
};
