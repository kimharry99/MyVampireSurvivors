// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"
#include "Waves/Wave.h"
#include "Waves/WaveDataAsset.h"
#include "Waves/WaveFactory.h"
#include "MyVamSurLogChannels.h"

void AWaveManager::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	WaveFactory = NewObject<UWaveFactory>(this);
	check(WaveFactory);
}

void AWaveManager::BeginPlay()
{
	Super::BeginPlay();

	CurrentWaveIndex = -1;
	UpdateUpcomingWaveData();
	TriggerUpcomingWave();
	SetPeriodTimer();
}

void AWaveManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if(UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(WavePeriodTimerHandle);
	}

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
	return CurrentWaveIndex;
}

float AWaveManager::GetTimeUntilNextWave() const
{
	if (UWorld* World = GetWorld())
	{
		if (World->GetTimerManager().IsTimerActive(WavePeriodTimerHandle))
		{
			return World->GetTimerManager().GetTimerRemaining(WavePeriodTimerHandle);
		}
	}
	return -1.0f;
}

bool AWaveManager::IsAllWavesTriggered() const
{
	return CurrentWaveIndex >= WaveTable.Num();
}

void AWaveManager::TriggerUpcomingWave()
{
	if (UpcomingWaveData == nullptr)
	{
		return;
	}

	if (WaveFactory == nullptr)
	{
		UE_LOG(LogMyVamSur, Warning, TEXT("Wave factory is not set"));
		return;
	}

	AWave* UpcomingWave = WaveFactory->CreateWave(UpcomingWaveData);
	UpcomingWave->OnWaveCleared.AddDynamic(this, &ThisClass::HandleWaveClear);
	UpcomingWave->Trigger();
	TriggeredWaves.Add(UpcomingWave);
}

void AWaveManager::UpdateUpcomingWaveData()
{
	if(WaveTable.IsValidIndex(++CurrentWaveIndex))
	{
		UpcomingWaveData = WaveTable[CurrentWaveIndex];
	}
	else
	{
		UpcomingWaveData = nullptr;
	}
}

void AWaveManager::SetPeriodTimer()
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(WavePeriodTimerHandle, this, &ThisClass::PostPeriodTimerComplete, WavePeriod);
	}
}

void AWaveManager::PostPeriodTimerComplete()
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(WavePeriodTimerHandle);
	}

	if (!IsAllWavesTriggered())
	{
		TriggerUpcomingWave();
		SetPeriodTimer();
		UpdateUpcomingWaveData();
	}
}

void AWaveManager::HandleWaveClear(AWave* ClearedWave)
{
	if (TriggeredWaves.Contains(ClearedWave))
	{
		TriggeredWaves.Remove(ClearedWave);
	}

	if (TriggeredWaves.Num() == 0 && IsAllWavesTriggered())
	{
		HandleAllWavesCleared();
	}
}

void AWaveManager::HandleAllWavesCleared()
{
	// Call game winning function
	UE_LOG(LogMyVamSur, Warning, TEXT("You Win!"));
}
