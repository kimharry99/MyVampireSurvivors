// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Wave.h"
#include "WaveList.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllWavesCleared);

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

	/** Delegate that is broadcasted when all waves in the list are cleared. */
	FOnAllWavesCleared OnAllWavesCleared;

protected:
	//~UObject Interface
	virtual void BeginDestroy() override;
	//~End UObject Interface

private:
	/** List of waves */
	TArray<TObjectPtr<UWave>> Waves;

	/** The number of remain waves. */
	int RemainWavesCount = 0;

	/**
	 * Wave cleared event handler.
	 * Decrease the number of remain waves.
	 * If the number of remain waves is 0, broadcast OnAllWavesCleared delegate.
	 */
	UFUNCTION()
	void HandleWaveCleared();
};
