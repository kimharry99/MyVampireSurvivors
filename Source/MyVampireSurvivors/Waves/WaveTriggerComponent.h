// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WaveTriggerComponent.generated.h"

class UWaveList;

/**
 * Component that can be attached to an actor to trigger a wave.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UWaveTriggerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWaveTriggerComponent();

protected:
	//~UActorComponent interface
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~End of UActorComponent interface

public:
	/**
	 * Start wave triggering.
	 * The component will trigger the waves periodically in the order they were set.
	 */
	void StartWave();

	/**
	 * Set WaveList.
	 */
	void SetWaveList(UWaveList* InWaveList);

	int GetCurrentWaveIndex() const;
	float GetTimeUntilNextWave() const;

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

	void TriggerCurrentWave();
	void StepToNextWave();
	void TriggerNextWave();

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
