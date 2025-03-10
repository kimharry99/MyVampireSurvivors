// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"

#include "MyVamSurLogChannels.h"
#include "Waves/Wave.h"
#include "Waves/WaveTriggerComponent.h"

AWaveManager::AWaveManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	WaveTriggerComponent = CreateDefaultSubobject<UWaveTriggerComponent>(TEXT("WaveTriggerComponent"));
	WaveTriggerComponent->OnWaveTriggered.AddDynamic(this, &ThisClass::HandleWaveTriggered);
}

void AWaveManager::BeginPlay()
{
	Super::BeginPlay();

	if (WaveTriggerComponent)
	{
		WaveTriggerComponent->SetWaveSchedule(WaveSchedule);
		WaveTriggerComponent->BeginWaveSchedule();
	}
}

void AWaveManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	for (AWave* Wave : TriggeredWaves)
	{
		if (Wave)
		{
			Wave->OnWaveCleared.RemoveAll(this);
		}
	}
}

int AWaveManager::GetCurrentWaveNumber() const
{
	check(WaveTriggerComponent);
	return WaveTriggerComponent->GetCurrentWaveIndex();
}

float AWaveManager::GetTimeUntilNextWave() const
{
	check(WaveTriggerComponent);
	return WaveTriggerComponent->GetTimeUntilNextWave();
}

void AWaveManager::HandleWaveTriggered(AWave* Wave)
{
	if (Wave)
	{
		Wave->OnWaveCleared.AddDynamic(this, &ThisClass::HandleWaveClear);
		TriggeredWaves.Add(Wave);
	}
}

void AWaveManager::HandleWaveClear(AWave* ClearedWave)
{
	if (TriggeredWaves.Contains(ClearedWave))
	{
		TriggeredWaves.Remove(ClearedWave);
	}

	check(WaveTriggerComponent);
	if (TriggeredWaves.Num() == 0 && WaveTriggerComponent->IsAllWavesTriggered())
	{
		HandleAllWavesCleared();
	}
}

void AWaveManager::HandleAllWavesCleared()
{
	// Call game winning function
	UE_LOG(LogMyVamSur, Warning, TEXT("You Win!"));
}
