// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyWaveManager.h"

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
	if (EnemyWaveDataTable == nullptr) return;

	// Load all enemy wave data
	static const FString ContextString(TEXT("Enemy Wave Data"));
	EnemyWaveDataTable->GetAllRows<FEnemyWaveInfo>(ContextString, WaveInfos);

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
	if (CurrentWaveIndex >= WaveInfos.Num())
	{
		// No more waves to trigger
		return;
	}

	// Get the current wave info
	FEnemyWaveInfo* WaveInfo = WaveInfos[CurrentWaveIndex];

	// Spawn enemies according to the wave info
	EnemySpawner->SpawnEnemyWave(*WaveInfo);

	// Set a timer to trigger the next wave
	if (World)
	{
		World->GetTimerManager().SetTimer(WaveHandle, this, &AEnemyWaveManager::TriggerNextWave, WavePeriod, false);
	}
}
