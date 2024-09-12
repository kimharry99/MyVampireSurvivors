// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveLoaderComponent.h"
#include "WaveTableRow.h"

// Sets default values for this component's properties
UWaveLoaderComponent::UWaveLoaderComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWaveLoaderComponent::OnRegister()
{
	Super::OnRegister();

	// Create subobject after Actor that owns this component is created
	WaveFactory = NewObject<UWaveFactory>(this, TEXT("WaveFactory"));
}

void UWaveLoaderComponent::AppendAllWaveToSchedule(FWaveSchedule& OutWaveSchedule)
{
	if (WaveDataTable == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("WaveDataTable is not set in WaveLoader."))
		return;
	}

	// Create wave instances from the wave records
	for (TMap<FName, uint8*>::TConstIterator RowMapIter(WaveDataTable->GetRowMap().CreateConstIterator()); RowMapIter; ++RowMapIter)
	{
		FWaveTableRow* WaveRecord = reinterpret_cast<FWaveTableRow*>(RowMapIter.Value());
		UWave* Wave = WaveFactory->CreateWave(WaveRecord->WaveDataAsset);
		if (Wave)
		{
			OutWaveSchedule.Add(*Wave);
		}
	}
}
