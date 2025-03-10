// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Wave.h"
#include "EnemyWave.generated.h"

class AEnemy;
class AEnemySpawner;
class UEnemyWaveDataAsset;
class UWaveDataAsset;

UCLASS()
class MYVAMPIRESURVIVORS_API AEnemyWave : public AWave_Deprecated
{
	GENERATED_BODY()

protected:
	//~AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~End of AActor interface

public:
	virtual void InitWaveData(const UWaveDataAsset* InWaveDataAsset) override;
	virtual void Trigger() override;

private:
	UPROPERTY()
	TObjectPtr<const UEnemyWaveDataAsset> EnemyWaveDataAsset;

	UPROPERTY()
	TObjectPtr<AEnemySpawner> EnemySpawner;

private:
	UPROPERTY()
	TArray<TObjectPtr<AEnemy>> SpawnedEnemies;

private:
	UFUNCTION()
	void HandleSpawnedEnemyDie(AEnemy* DiedEnemy);
};
