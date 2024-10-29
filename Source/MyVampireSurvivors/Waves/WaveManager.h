// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveManager.generated.h"

class AWave;
class UWaveDataAsset;
class UWaveFactory;

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
	/**
	 * A data table containing ordered enemy wave data.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Wave", meta = (PrivateAllowAccess = "true"))
	TArray<TObjectPtr<UWaveDataAsset>> WaveTable;

	/**
	 * The period(sec) between enemy waves.
	 */
	UPROPERTY(EditAnywhere, Category = "Wave", meta = (AllowPrivateAccess = "true"))
	float WavePeriod = 3.0f;

	int CurrentWaveIndex = -1;

	UPROPERTY()
	TObjectPtr<UWaveDataAsset> UpcomingWaveData = nullptr;

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
