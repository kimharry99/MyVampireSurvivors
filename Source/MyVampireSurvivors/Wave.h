// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Wave.generated.h"

/**
 * Base class for wave.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UWave : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * Trigger the wave
	 */
	virtual void Trigger();

protected:
	/**
	 * Hide the constructor to prevent instantiation
	 */
	UWave();
};
