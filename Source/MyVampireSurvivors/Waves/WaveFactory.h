// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class AWave;
class UWaveDataAsset;

struct MYVAMPIRESURVIVORS_API FWaveFactory
{
private:
	FWaveFactory() = default;

public:
	static AWave* CreateWave(const UWaveDataAsset* WaveDataAsset, AActor* WaveOwner);
};
