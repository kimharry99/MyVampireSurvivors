// Fill out your copyright notice in the Description page of Project Settings.


#include "Waves/WaveClearHandlerComponent.h"

#include "MyVamSurLogChannels.h"
#include "Waves/Wave.h"

UWaveClearHandlerComponent::UWaveClearHandlerComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UWaveClearHandlerComponent::IsTriggeringWaveRemaining() const
{
	return !TriggeredWaves.IsEmpty();
}

void UWaveClearHandlerComponent::HandleWaveTriggered(AWave* Wave)
{
	if (Wave)
	{
		Wave->OnWaveCleared.AddDynamic(this, &ThisClass::HandleWaveClear);
		TriggeredWaves.Add(Wave);
	}
}

void UWaveClearHandlerComponent::HandleWaveClear(AWave* ClearedWave)
{
	check(TriggeredWaves.Contains(ClearedWave));
	TriggeredWaves.Remove(ClearedWave);

	OnWaveCleared.Broadcast();
}

void UWaveClearHandlerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for (TWeakObjectPtr<AWave> Wave : TriggeredWaves)
	{
		if (Wave.IsValid())
		{
			Wave->OnWaveCleared.RemoveAll(this);
		}
	}

	Super::EndPlay(EndPlayReason);
}
