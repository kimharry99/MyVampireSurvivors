// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WaveScheduleData.generated.h"

class UWaveDataAsset;

/**
 *
 */
UCLASS(Const, BlueprintType, ClassGroup = Wave)
class MYVAMPIRESURVIVORS_API UWaveScheduleData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditInstanceOnly, Category = "Wave")
	TArray<TObjectPtr<const UWaveDataAsset>> SortedWaves;

	/** The period(sec) between waves. */
	UPROPERTY(EditInstanceOnly, Category = "Wave")
	float WavePeriod = 3.0f;
};
