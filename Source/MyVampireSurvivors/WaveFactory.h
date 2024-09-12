// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WaveDataAsset.h"
#include "Wave.h"
#include "EnemySpawner.h"
#include "WaveFactory.generated.h"

/**
 * 
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UWaveFactory : public UObject
{
	GENERATED_BODY()

public:
	UWaveFactory();

	/**
	 * Create a wave from the given wave data asset.
	 */
	UWave* CreateWave(const UWaveDataAsset* WaveDataAsset) const;

private:
	/** Set as member of UEnemyWave. */
	UPROPERTY()
	TObjectPtr<UEnemySpawner> EnemySpawner;
};
