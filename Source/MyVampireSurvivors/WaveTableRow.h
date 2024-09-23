// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WaveDataAsset.h"
#include "WaveTableRow.generated.h"

/**
 * Struct for managing wave data assets in a data table.
 */
USTRUCT(BlueprintType)
struct MYVAMPIRESURVIVORS_API FWaveTableRow : public FTableRowBase
{
	GENERATED_BODY()

	/**
	 * Wave data asset.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	UWaveDataAsset* WaveDataAsset;
};
