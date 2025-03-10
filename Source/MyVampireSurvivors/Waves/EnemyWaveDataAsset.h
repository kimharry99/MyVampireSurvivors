// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WaveDataAsset.h"
#include "EnemyWaveDataAsset.generated.h"

struct FEnemySpawnRecord;

/**
 * Enemy wave data asset.
 * Save the spawning enemy and their counts.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UEnemyWaveDataAsset : public UWaveDataAsset
{
	GENERATED_BODY()

public:
	UEnemyWaveDataAsset(const FObjectInitializer& ObjectInitializer);

	/** Return the enemy spawn record group. */
	TArray<FEnemySpawnRecord> GetSpawningEnemyGroup() const;

private:
	/** Group of enemies to spawn. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies", meta = (AllowPrivateAccess = "true"))
	TArray<FEnemySpawnRecord> SpawningEnemyGroup;
};
