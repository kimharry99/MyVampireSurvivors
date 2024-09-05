// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WaveDataAsset.generated.h"

/**
 * Base data asset for waves.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UWaveDataAsset : public UDataAsset
{
	GENERATED_BODY()

protected:
	/**
	 * Don't create the object of this class.
	 */
	UWaveDataAsset();
};
