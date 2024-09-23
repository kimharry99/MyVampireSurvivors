// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveList.h"
#include "WaveLoaderComponent.h"
#include "WaveTriggerComponent.h"
#include "WaveManager.generated.h"

/**
 * WaveManager handles ordered waves.
 *
 * It triggers an initial wave when the game starts.
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
	//~AActor Interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~End of AActor Interface

private:
	/** Wave data loader from a data table */
	UPROPERTY(EditDefaultsOnly, meta = (PrivateAllowAccess = "true"))
	TObjectPtr<UWaveLoaderComponent> WaveLoader;

	/** This class triggers waves periodically. */
	UPROPERTY(EditDefaultsOnly, meta = (PrivateAllowAccess = "true"))
	TObjectPtr<UWaveTriggerComponent> WaveTrigger;

	/**
	 * A data table containing ordered enemy wave data.
	 */
	UPROPERTY(EditDefaultsOnly, meta = (PrivateAllowAccess = "true"))
	TObjectPtr<UDataTable> WaveDataTable = nullptr;

	UPROPERTY()
	TObjectPtr<UWaveList> WaveList = nullptr;

	/**
	 * Event handler for all waves cleared.
	 * Call game winning function.
	 */
	UFUNCTION()
	void HandleAllWavesCleared();
};
