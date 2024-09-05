// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyWaveManager.h"
#include "WaveDataAsset.h"
#include "EnemyWaveDataAsset.h"

AEnemyWaveManager::AEnemyWaveManager()
{
	PrimaryActorTick.bCanEverTick = false;

	EnemySpawner = CreateDefaultSubobject<UEnemySpawner>(TEXT("EnemySpawner"));
}

void AEnemyWaveManager::BeginPlay()
{
	Super::BeginPlay();

	// Start the first wave
	StartWave();
}

void AEnemyWaveManager::StartWave()
{
	if (WaveDataTable == nullptr) return;

	// Load all enemy wave data
	static const FString ContextString(TEXT("Wave Data"));
	WaveDataTable->GetAllRows<FWaveTableRow>(ContextString, WaveRecords);

	// Call TriggerNextWave method after the wave period
	CurrentWaveIndex = -1;
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(WaveHandle, this, &AEnemyWaveManager::TriggerNextWave, WavePeriod, false);
	}
}

void AEnemyWaveManager::TriggerNextWave()
{
	// Clear previous wave handle
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().ClearTimer(WaveHandle);
	}

	// Increment the current wave index
	CurrentWaveIndex++;

	// Check if the current wave index is valid
	if (CurrentWaveIndex >= WaveRecords.Num())
	{
		// No more waves to trigger
		return;
	}

	// Get the current wave info
	UWaveDataAsset* WaveRecord = WaveRecords[CurrentWaveIndex]->WaveDataAsset;

	// Spawn enemies according to the wave info
	UEnemyWaveDataAsset* EnemyWaveDataAsset = Cast<UEnemyWaveDataAsset>(WaveRecord);
	EnemySpawner->SpawnEnemyWave(EnemyWaveDataAsset);

	// Set a timer to trigger the next wave
	if (World)
	{
		World->GetTimerManager().SetTimer(WaveHandle, this, &AEnemyWaveManager::TriggerNextWave, WavePeriod, false);
	}
}
