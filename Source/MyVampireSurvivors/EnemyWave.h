// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Wave.h"
#include "EnemyWaveDataAsset.h"
#include "EnemyWave.generated.h"

/**
 * 
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UEnemyWave : public UWave
{
	GENERATED_BODY()

public:
	/**
	 * Create an enemy wave from the given enemy wave data asset.
	 *
	 * @param WaveDataAsset Wave data asset to create enemy wave from. It must be EnemyWaveDataAsset.
	 * @return Created enemy wave.
	 */
	static UEnemyWave* CreateEnemyWave(const UWaveDataAsset* WaveDataAsset);

protected:
	/**
	 * Trigger the wave.
	 *
	 * Spawn enemies based on enemy wave data asset.
	 */
	virtual void Trigger() override;

private:
	UEnemyWave() = default;

	/** Enemy wave data asset. */
	const UEnemyWaveDataAsset* EnemyWaveDataAsset;
};
