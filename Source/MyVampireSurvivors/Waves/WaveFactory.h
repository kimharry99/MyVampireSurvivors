// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WaveDataAsset.h"
#include "Wave.h"
#include "Enemies/EnemySpawner.h"
#include "WaveFactory.generated.h"

/**
 * 
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UWaveFactory : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * Create a wave from the given wave data asset.
	 */
	UWave* CreateWave(const UWaveDataAsset* WaveDataAsset) const;

	/**
	 * Set enemy spawner property.
	 * 
	 * @param InEnemySpawner Enemy spawner to set.
	 */
	void SetEnemySpawner(AEnemySpawner* InEnemySpawner);

private:
	/** Set as member of UEnemyWave. */
	UPROPERTY()
	TObjectPtr<AEnemySpawner> EnemySpawner;
};
