// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Wave.h"
#include "WaveList.generated.h"

/**
 * Wave container.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UWaveList : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * Add a wave to the list.
	 * 
	 * @param NewWave - The wave to add
	 */
	void Add(UWave* NewWave);

	/**
	 * Get the number of waves in the list.
	 * Returns nullptr if the index is out of bounds.
	 * 
	 * @param Index - The index of the wave to get
	 * @return The wave at the specified index. Returns nullptr if the index is out of bounds.
	 */
	UWave* GetWave(int Index) const;

private:
	/** List of waves */
	TArray<TObjectPtr<UWave>> Waves;
};
