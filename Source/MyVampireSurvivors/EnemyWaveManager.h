// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyWaveInfo.h"
#include "EnemySpawner.h"
#include "EnemyWaveManager.generated.h"

/**
 * EnemyWaveManager handles ordered enemy waves.
 * 
 * It triggers an initial enemy wave when the game starts.
 * After a cooldown period in the enemey wave has passed, the class will trigger the next enemy wave.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API AEnemyWaveManager : public AActor
{
	GENERATED_BODY()

public:
	AEnemyWaveManager();

protected:
	virtual void BeginPlay() override;

private:
	/**
	 * Trigger the first enemy wave.
	 */
	void StartWave();

	/*
	 * Trigger the next enemy wave.
	 */
	void TriggerNextWave();

	/**
	 * A data table containing ordered enemy wave data.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UDataTable* EnemyWaveDataTable = nullptr;

	/**
	 * The enemy spawner that will spawn enemies according to the enemy wave data.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UEnemySpawner* EnemySpawner;

	/**
	 * A list of enemy wave data loaded from the data table.
	 */
	TArray<FEnemyWaveInfo*> WaveInfos;

	/**
	 * The index of the current enemy wave.
	 */
	int CurrentWaveIndex = -1;

	/**
	 * A timer handle to trigger the next enemy wave.
	 */
	FTimerHandle WaveHandle;

	/**
	 * The period(sec) between enemy waves.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float WavePeriod = 5.0f;
};
