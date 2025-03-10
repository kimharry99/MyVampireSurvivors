// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"

#include "MyVamSurLogChannels.h"
#include "Waves/Wave.h"
#include "Waves/WaveDataAsset.h"
#include "Waves/WaveFactory.h"
#include "Waves/WaveScheduleData.h"
#include "Waves/WaveTriggerComponent.h"

AWaveManager::AWaveManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	WaveTriggerComponent = CreateDefaultSubobject<UWaveTriggerComponent>(TEXT("WaveTriggerComponent"));
	WaveTriggerComponent->OnWaveTriggered.AddDynamic(this, &ThisClass::HandleWaveTriggered);
}

void AWaveManager::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	WaveFactory = NewObject<UWaveFactory>(this);
	check(WaveFactory);
}

void AWaveManager::BeginPlay()
{
	Super::BeginPlay();

	if (WaveTriggerComponent)
	{
		WaveTriggerComponent->SetWaveSchedule(WaveSchedule);
		WaveTriggerComponent->BeginWaveSchedule();
	}

	//WavePeriod = WaveSchedule ? WaveSchedule->WavePeriod : 3.0f;

	//CurrentWaveIndex = -1;
	//UpdateUpcomingWaveData();
	//TriggerUpcomingWave();
	//SetPeriodTimer();
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
	check(WaveTriggerComponent);
	return WaveTriggerComponent->GetCurrentWaveIndex();
}

float AWaveManager::GetTimeUntilNextWave() const
{
	check(WaveTriggerComponent);
	return WaveTriggerComponent->GetTimeUntilNextWave();
}

bool AWaveManager::IsAllWavesTriggered() const
{
	if (!WaveSchedule)
	{
		UE_LOG(LogMyVamSur, Warning, TEXT("WaveSchedule is not set in IsAllWavesTriggered [%s]."), *GetPathNameSafe(this));
		return false;
	}

	return CurrentWaveIndex >= WaveSchedule->SortedWaves.Num();
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
	if (!WaveSchedule)
	{
		UE_LOG(LogMyVamSur, Warning, TEXT("WaveSchedule is not set in UpdateUpcomingWaveData [%s]."), *GetPathNameSafe(this));
		return;
	}

	++CurrentWaveIndex;
	if (WaveSchedule->SortedWaves.IsValidIndex(CurrentWaveIndex))
	{
		UpcomingWaveData = WaveSchedule->SortedWaves[CurrentWaveIndex];
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
