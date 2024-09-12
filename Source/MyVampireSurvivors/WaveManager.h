// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/** Wave data loader from a data table */
	UPROPERTY(EditDefaultsOnly, meta = (PrivateAllowAccess = "true"))
	TObjectPtr<UWaveLoaderComponent> WaveLoader;

	UPROPERTY(EditDefaultsOnly, meta = (PrivateAllowAccess = "true"))
	TObjectPtr<UWaveTriggerComponent> WaveTrigger;
};
