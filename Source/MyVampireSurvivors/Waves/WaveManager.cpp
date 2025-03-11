// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"

#include "MyVamSurLogChannels.h"
#include "Waves/WaveClearHandlerComponent.h"
#include "Waves/WaveTriggerComponent.h"

AWaveManager::AWaveManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	ClearHandlerComponent = CreateDefaultSubobject<UWaveClearHandlerComponent>(TEXT("ClearHandlerComponent"));
	ClearHandlerComponent->OnWaveCleared.Add(FSimpleMulticastDelegate::FDelegate::CreateUObject(this, &ThisClass::VerifyAllWavesCleared));

	WaveTriggerComponent = CreateDefaultSubobject<UWaveTriggerComponent>(TEXT("WaveTriggerComponent"));
	WaveTriggerComponent->OnWaveTriggered.AddDynamic(ClearHandlerComponent, &UWaveClearHandlerComponent::HandleWaveTriggered);
}

void AWaveManager::BeginPlay()
{
	Super::BeginPlay();

	check(WaveTriggerComponent);
	WaveTriggerComponent->SetWaveSchedule(WaveSchedule);
	WaveTriggerComponent->BeginWaveSchedule();
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

void AWaveManager::VerifyAllWavesCleared()
{
	if (IsAllWavesCleared())
	{
		UE_LOG(LogMyVamSur, Warning, TEXT("You Win!"));
	}
}

bool AWaveManager::IsAllWavesCleared() const
{
	check(ClearHandlerComponent);
	check(WaveTriggerComponent);
	return !ClearHandlerComponent->IsAnyTriggeredWaveUncleared() && WaveTriggerComponent->IsWaveScheduleDone();
}
