// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"

#include "MyVamSurLogChannels.h"
#include "Waves/WaveClearHandlerComponent.h"
#include "Waves/WaveTriggerComponent.h"

AWaveManager::AWaveManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ClearHandlerComponent = CreateDefaultSubobject<UWaveClearHandlerComponent>(TEXT("ClearHandlerComponent"));
	ClearHandlerComponent->OnWaveCleared.Add(FSimpleMulticastDelegate::FDelegate::CreateUObject(this, &ThisClass::DetermineAllWaveCleared));

	WaveTriggerComponent = CreateDefaultSubobject<UWaveTriggerComponent>(TEXT("WaveTriggerComponent"));
	WaveTriggerComponent->OnWaveTriggered.AddDynamic(ClearHandlerComponent, &UWaveClearHandlerComponent::HandleWaveTriggered);
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

void AWaveManager::DetermineAllWaveCleared()
{
	check(ClearHandlerComponent);
	check(WaveTriggerComponent);

	if (!ClearHandlerComponent->IsTriggeringWaveRemaining() && WaveTriggerComponent->IsAllWavesTriggered())
	{
		UE_LOG(LogMyVamSur, Warning, TEXT("You Win!"));
	}
}
