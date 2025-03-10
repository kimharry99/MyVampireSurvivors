// Fill out your copyright notice in the Description page of Project Settings.


#include "Waves/WaveTriggerComponent.h"

#include "MyVamSurLogChannels.h"
#include "Waves/Wave.h"
#include "Waves/WaveDataAsset.h"
#include "Waves/WaveFactory.h"
#include "Waves/WaveScheduleData.h"

UWaveTriggerComponent::UWaveTriggerComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;

	WaveFactory = CreateDefaultSubobject<UWaveFactory>(TEXT("WaveFactory"));
}

void UWaveTriggerComponent::SetWaveSchedule(const UWaveScheduleData* NewWaveScheduleData)
{
	if (!NewWaveScheduleData)
	{
		UE_LOG(LogMyVamSur, Warning, TEXT("Input NewWaveScheduleData is null in SetWaveSchedule [%s]."), *GetPathNameSafe(this));
		return;
	}

	WaveSequence = NewWaveScheduleData->SortedWaves;
	WavePeriod = NewWaveScheduleData->WavePeriod;
}

void UWaveTriggerComponent::BeginWaveSchedule()
{
	UpcomingWaveIndex = 0;
	TriggerUpcomingWave();
}

int UWaveTriggerComponent::GetCurrentWaveIndex() const
{
	return UpcomingWaveIndex - 1;
}

float UWaveTriggerComponent::GetTimeUntilNextWave() const
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

bool UWaveTriggerComponent::IsAllWavesTriggered() const
{
	return UpcomingWaveIndex >= WaveSequence.Num();
}

void UWaveTriggerComponent::TriggerUpcomingWave()
{
	if (WaveSequence.IsValidIndex(UpcomingWaveIndex))
	{
		const UWaveDataAsset* UpcomingWaveData = WaveSequence[UpcomingWaveIndex];
		check(WaveFactory);
		if (AWave* UpcomingWave = WaveFactory->CreateWave(UpcomingWaveData))
		{
			UpcomingWave->Trigger();
			OnWaveTriggered.Broadcast(UpcomingWave);

			++UpcomingWaveIndex;
			SetPeriodTimer();
		}
	}
}

void UWaveTriggerComponent::SetPeriodTimer()
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(WavePeriodTimerHandle, FTimerDelegate::CreateUObject(this, &ThisClass::OnPeriodTimerCompleted), WavePeriod, false);
	}
}

void UWaveTriggerComponent::OnPeriodTimerCompleted()
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(WavePeriodTimerHandle);
	}

	if (!IsAllWavesTriggered())
	{
		TriggerUpcomingWave();
		SetPeriodTimer();
	}
}
