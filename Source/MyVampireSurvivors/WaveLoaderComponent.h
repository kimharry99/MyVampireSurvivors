// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Wave.h"
#include "WaveFactory.h"
#include "WaveList.h"
#include "WaveLoaderComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYVAMPIRESURVIVORS_API UWaveLoaderComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWaveLoaderComponent();

	/**
	 * Load waves from input data table.
	 * 
	 * @param InWaveDataTable -  The data table to load waves from
	 * @return Instance of UWaveList loaded from the data table
	 */
	UWaveList* LoadWavesFromDataTable(UDataTable* InWaveDataTable) const;

protected:
	virtual void BeginPlay() override;
	virtual void OnRegister() override;

private:
	/** Create UWave instance from wave data table row. */
	UPROPERTY()
	TObjectPtr<UWaveFactory> WaveFactory;
};
