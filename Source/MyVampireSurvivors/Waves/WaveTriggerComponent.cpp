// Fill out your copyright notice in the Description page of Project Settings.


#include "Waves/WaveTriggerComponent.h"

#include "MyVamSurLogChannels.h"
#include "Waves/Wave.h"
#include "Waves/WaveDefinition.h"
#include "Waves/WaveScheduleData.h"

UWaveTriggerComponent::UWaveTriggerComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWaveTriggerComponent::SetWaveSchedule(const UWaveScheduleData* NewWaveScheduleData)
{
	if (!NewWaveScheduleData)
	{
		UE_LOG(LogMyVamSur, Warning, TEXT("Input NewWaveScheduleData is null in SetWaveSchedule [%s]."), *GetPathNameSafe(this));
		return;
	}

	WavePeriod = NewWaveScheduleData->WavePeriod;
	WaveSequence = NewWaveScheduleData->SortedWaves;
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

bool UWaveTriggerComponent::IsWaveScheduleDone() const
{
	return UpcomingWaveIndex >= WaveSequence.Num();
}

void UWaveTriggerComponent::TriggerUpcomingWave()
{
	if (WaveSequence.IsValidIndex(UpcomingWaveIndex))
	{
		if (const UWaveDefinition* UpcomingWaveData = WaveSequence[UpcomingWaveIndex])
		{
			if (UWorld* World = GetWorld())
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = GetOwner();

				if (AWave* UpcomingWave = World->SpawnActor<AWave>(SpawnParams))
				{
					UpcomingWave->Trigger(UpcomingWaveData->ActorsToSpawn);
					OnWaveTriggered.Broadcast(UpcomingWave);
				}
			}
		}
		else
		{
			UE_LOG(LogMyVamSur, Warning, TEXT("UWaveTriggerComponent::WaveSequence[%d] is null."), UpcomingWaveIndex);
		}

		++UpcomingWaveIndex;
		// If there are more waves to trigger, set up a timer for the next wave.
		if (!IsWaveScheduleDone())
		{
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

	if (!IsWaveScheduleDone())
	{
		TriggerUpcomingWave();
		SetPeriodTimer();
	}
}
