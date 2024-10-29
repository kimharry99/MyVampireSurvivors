// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WaveDataAsset.h"
#include "Wave.h"
#include "Enemies/EnemySpawner.h"
#include "WaveFactory.generated.h"

UCLASS()
class MYVAMPIRESURVIVORS_API UWaveFactory : public UObject
{
	GENERATED_BODY()

public:
	AWave* CreateWave(const UWaveDataAsset* WaveDataAsset) const;
};
