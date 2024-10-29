// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemies/EnemySpawner.h"
#include "Wave.h"
#include "WaveFactory.h"
#include "EnemyWave.generated.h"

class UEnemyWaveDataAsset;

UCLASS()
class MYVAMPIRESURVIVORS_API AEnemyWave : public AWave
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
