// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveManager.generated.h"

class UWaveClearHandlerComponent;
class UWaveScheduleData;
class UWaveTriggerComponent;

/**
 *
 * WaveManager is responsible for handling the wave system, ensuring that waves are triggered
 * and cleared appropriately. It utilizes UWaveClearHandlerComponent to track wave completion
 * and UWaveTriggerComponent to schedule and start new waves.
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

	/** Checks if all waves have been cleared and triggers the win condition if true. */
	void VerifyAllWavesCleared();

	bool IsAllWavesCleared() const;
};
