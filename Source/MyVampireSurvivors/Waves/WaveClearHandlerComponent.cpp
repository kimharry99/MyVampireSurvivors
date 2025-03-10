// Fill out your copyright notice in the Description page of Project Settings.


#include "Waves/WaveClearHandlerComponent.h"

#include "MyVamSurLogChannels.h"
#include "Waves/Wave.h"

UWaveClearHandlerComponent::UWaveClearHandlerComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UWaveClearHandlerComponent::IsAnyTriggeredWaveUncleared() const
{
	return !TriggeredWaves.IsEmpty();
}

void UWaveClearHandlerComponent::HandleWaveTriggered(AWave_Deprecated* Wave)
{
	if (Wave)
	{
		Wave->OnWaveCleared.AddDynamic(this, &ThisClass::HandleWaveClear);
		TriggeredWaves.Add(Wave);
	}
}

void UWaveClearHandlerComponent::HandleWaveClear(AWave_Deprecated* ClearedWave)
{
	check(TriggeredWaves.Contains(ClearedWave));
	TriggeredWaves.Remove(ClearedWave);

	OnWaveCleared.Broadcast();
}

void UWaveClearHandlerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for (TWeakObjectPtr<AWave_Deprecated> Wave : TriggeredWaves)
	{
		if (Wave.IsValid())
		{
			// Unbinds all wave-cleared events to prevent dangling references.
			Wave->OnWaveCleared.RemoveAll(this);
		}
	}

	Super::EndPlay(EndPlayReason);
}
