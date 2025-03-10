// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WaveDataAsset.generated.h"

/** Types of waves. */
UENUM(BlueprintType)
enum class EWaveType : uint8
{
	Undefined	UMETA(DisplayName = "Undefined"),	// Undefined wave, used in base wave class.
	Enemy		UMETA(DisplayName = "Enemy"),		// Wave that spawns enemies. 
	Event		UMETA(DisplayName = "Event"),		// Wave that triggers events. 
};

/**
 * Base data asset for waves.
 */
UCLASS(Abstract, Const, BlueprintType, ClassGroup = "Wave")
class MYVAMPIRESURVIVORS_API UWaveDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	EWaveType WaveType = EWaveType::Undefined;

protected:
	/**
	 * Don't create the object of this class.
	 */
	UWaveDataAsset(const FObjectInitializer& ObjectInitializer);
};
