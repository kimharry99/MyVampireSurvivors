// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wave.h"
#include "WaveManager.generated.h"

/**
 * WaveManager handles ordered waves.
 *
 * It triggers an initial enemy wave when the game starts.
 * After a cooldown period in the wave has passed, the class will trigger the next wave.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API AWaveManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/**
	 * Load all wave records from data table.
	 */
	void LoadWaveRecords();

	/**
	 * Trigger current wave.
	 */
	void TriggerCurrentWave();

	/**
	 * Called when the current wave is triggered.
	 */
	void PostCurrentWaveTriggerd();

	/**
	 * Set a timer to trigger next wave after duration.
	 */
	void ReserveNextWave();

	/**
	 * A data table containing ordered enemy wave data.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UDataTable* WaveDataTable = nullptr;

	/**
	 * Container of waves.
	 */
	TArray<UWave*> Waves;

	int CurrentWaveIndex = -1;

	/**
	 * A timer handle to trigger the next enemy wave.
	 */
	FTimerHandle WaveHandle;

	/**
	 * The period(sec) between enemy waves.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float WavePeriod = 3.0f;;
};
