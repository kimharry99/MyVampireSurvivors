// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveManager.generated.h"

class UWaveClearHandlerComponent;
class UWaveScheduleData;
class UWaveTriggerComponent;

/**
 * WaveManager handles periodical event waves.
 *
 * It triggers an initial wave when the game starts.
 * After a cooldown period in the wave has passed, the class will trigger the next wave.
 */
UCLASS(ClassGroup = "Wave")
class MYVAMPIRESURVIVORS_API AWaveManager : public AActor
{
	GENERATED_BODY()

public:
	AWaveManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	//~AActor Interface
	virtual void BeginPlay() override;
	//~End of AActor Interface

public:
	int GetCurrentWaveNumber() const;
	float GetTimeUntilNextWave() const;

private:
	UPROPERTY(VisibleAnywhere, Category = "Wave")
	TObjectPtr<UWaveTriggerComponent> WaveTriggerComponent;

	UPROPERTY(VisibleAnywhere, Category = "Wave")
	TObjectPtr<UWaveClearHandlerComponent> ClearHandlerComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	TObjectPtr<const UWaveScheduleData> WaveSchedule;

	void DetermineAllWaveCleared();
};
