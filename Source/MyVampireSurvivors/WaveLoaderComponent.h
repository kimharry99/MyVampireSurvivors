// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Wave.h"
#include "WaveFactory.h"
#include "WaveSchedule.h"
#include "WaveLoaderComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYVAMPIRESURVIVORS_API UWaveLoaderComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWaveLoaderComponent();

	/**
	 * Append all wave in data table to the schedule.
	 * 
	 * @param OutWaveSchedule The wave schedule to append the wave to
	 */
	void AppendAllWaveToSchedule(FWaveSchedule& OutWaveSchedule);

protected:
	virtual void BeginPlay() override;
	virtual void OnRegister() override;

private:
	/**
	 * A data table containing ordered enemy wave data.
	 */
	UPROPERTY(EditDefaultsOnly, meta = (PrivateAllowAccess = "true"))
	TObjectPtr<UDataTable> WaveDataTable = nullptr;

	/** Create UWave instance from wave data table row. */
	UPROPERTY()
	TObjectPtr<UWaveFactory> WaveFactory;
};
