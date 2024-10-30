// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WaveFactory.generated.h"

class AWave;
class UWaveDataAsset;

UCLASS()
class MYVAMPIRESURVIVORS_API UWaveFactory : public UObject
{
	GENERATED_BODY()

public:
	AWave* CreateWave(const UWaveDataAsset* WaveDataAsset) const;
};
