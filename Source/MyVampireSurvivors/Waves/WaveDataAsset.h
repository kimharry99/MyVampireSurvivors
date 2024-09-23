// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WaveDataAsset.generated.h"

/**
 * Types of waves.
 */
enum EWaveType : uint8
{
	/**
	 * Undefined wave, used in base wave class.
	 */
	Undefined UMETA(DisplayName = "Undefined"),

	/**
	 * Wave that spawns enemies.
	 */
	Enemy UMETA(DisplayName = "Enemy"),

	/**
	 * Wave that triggers events.
	 */
	Event UMETA(DisplayName = "Event"),
};

/**
 * Base data asset for waves.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UWaveDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	EWaveType WaveType = EWaveType::Undefined;

protected:
	/**
	 * Don't create the object of this class.
	 */
	UWaveDataAsset();
};
