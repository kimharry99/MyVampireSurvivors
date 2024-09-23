// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WaveDataAsset.h"
#include "Enemies/EnemySpawnRecord.h"
#include "EnemyWaveDataAsset.generated.h"

/**
 * Enemy wave data asset.
 * Save the spawning enemy and their counts.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UEnemyWaveDataAsset : public UWaveDataAsset
{
	GENERATED_BODY()

public:
	UEnemyWaveDataAsset();
	/**
	 * Return the enemy spawn record group.
	 */
	const TArray<FEnemySpawnRecord>& GetSpawningEnemyGroup() const;

private:
	/**
	 * Group of enemies to spawn.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemies", meta = (AllowPrivateAccess = "true"))
	TArray<FEnemySpawnRecord> SpawningEnemyGroup;
};
