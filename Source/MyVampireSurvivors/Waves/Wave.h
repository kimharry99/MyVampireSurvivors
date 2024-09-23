// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Wave.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWaveCleared);

/**
 * Base class for wave.
 */
UCLASS(Abstract)
class MYVAMPIRESURVIVORS_API UWave : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * Trigger the wave.
	 */
	virtual void Trigger();

	/** Delegate that is broadcasted when the wave is cleared. */
	FOnWaveCleared OnWaveCleared;

protected:
	/**
	 * Clear the wave.
	 * Broadcast OnWaveCleared delegate.
	 * Call PostWaveCleared function.
	 */
	virtual void ClearWave();

	/**
	 * Called when the wave is cleared.
	 */
	virtual void PostWaveCleared();
};
