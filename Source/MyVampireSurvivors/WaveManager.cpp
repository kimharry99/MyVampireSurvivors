// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"
#include "WaveTableRow.h"
#include "WaveFactory.h"

// Sets default values
AWaveManager::AWaveManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WaveFactory = CreateDefaultSubobject<UWaveFactory>(TEXT("WaveFactory"));
}

// Called when the game starts or when spawned
void AWaveManager::BeginPlay()
{
	Super::BeginPlay();

	LoadWaveRecords();

	CurrentWaveIndex = 0;
	TriggerCurrentWave();
}

void AWaveManager::LoadWaveRecords()
{
	if (WaveDataTable == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("WaveDataTable is not set in WaveManager."));
		return;
	}

	// Load all enemy wave data
	static const FString ContextString(TEXT("Wave Data"));
	TArray<FWaveTableRow*> WaveRecords;
	WaveDataTable->GetAllRows<FWaveTableRow>(ContextString, WaveRecords);

	// Create wave instances from the wave records
	for (FWaveTableRow* WaveRecord : WaveRecords)
	{
		UWave* Wave = WaveFactory->CreateWave(WaveRecord->WaveDataAsset);
		if (Wave)
		{
			Waves.Add(Wave);
		}
	}
}

void AWaveManager::TriggerCurrentWave()
{
	if (CurrentWaveIndex >= Waves.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("No more waves"));
		return;
	}

	UWave* CurrentWave = Waves[CurrentWaveIndex];
	CurrentWave->Trigger();

	PostCurrentWaveTriggerd();
}

void AWaveManager::PostCurrentWaveTriggerd()
{
	ReserveNextWave();
}

void AWaveManager::ReserveNextWave()
{
	// Increment the current wave index
	CurrentWaveIndex++;

	// Set a timer to trigger the next wave
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().ClearTimer(WaveHandle);
		World->GetTimerManager().SetTimer(WaveHandle, this, &AWaveManager::TriggerCurrentWave, WavePeriod, false);
	}
}
