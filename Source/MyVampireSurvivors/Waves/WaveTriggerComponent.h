// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Wave.h"
#include "WaveList.h"
#include "WaveTriggerComponent.generated.h"

/**
 * Component that can be attached to an actor to trigger a wave.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYVAMPIRESURVIVORS_API UWaveTriggerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWaveTriggerComponent();

	/**
	 * Start wave triggering.
	 * The component will trigger the waves periodically in the order they were set.
	 */
	void StartWave();

	/**
	 * Set WaveList.
	 */
	void SetWaveList(UWaveList* InWaveList);

private:
	/**
	 * The period(sec) between enemy waves.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float WavePeriod = 3.0f;

	/** The WaveList to trigger. */
	UPROPERTY()
	TObjectPtr<UWaveList> WaveList = nullptr;

	int CurrentWaveIndex = 0;

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
	 * A timer handle to trigger the next enemy wave.
	 */
	FTimerHandle WaveHandle;
};
