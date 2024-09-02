// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemySpawnInfo.h"
#include "EnemyWaveInfo.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FEnemyWaveInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int WaveNumber;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TArray<FEnemySpawnInfo> EnemySpawnInfos;
};
