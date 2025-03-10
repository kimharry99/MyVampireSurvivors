// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WaveScheduleData.generated.h"

class UWaveDefinition;

/**
 *
 */
UCLASS(Const, BlueprintType, ClassGroup = Wave)
class MYVAMPIRESURVIVORS_API UWaveScheduleData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	TArray<TObjectPtr<const UWaveDefinition>> SortedWaves;

	/** The period(sec) between waves. */
	UPROPERTY(EditInstanceOnly, Category = "Wave")
	float WavePeriod = 3.0f;
};
