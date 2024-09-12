// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"

// Sets default values
AWaveManager::AWaveManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WaveLoader = CreateDefaultSubobject<UWaveLoaderComponent>(TEXT("WaveLoader"));
	WaveTrigger = CreateDefaultSubobject<UWaveTriggerComponent>(TEXT("WaveTrigger"));
}

// Called when the game starts or when spawned
void AWaveManager::BeginPlay()
{
	Super::BeginPlay();

	WaveLoader->AppendAllWaveToSchedule(WaveTrigger->GetWaveSchedule());
	WaveTrigger->StartWave();
}
