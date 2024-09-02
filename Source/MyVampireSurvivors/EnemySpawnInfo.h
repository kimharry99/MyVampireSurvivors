// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "EnemySpawnInfo.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct MYVAMPIRESURVIVORS_API FEnemySpawnInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int32 Count;
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TSubclassOf<AEnemy> EnemyClass;
};
