// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/MyVamSurGameState.h"
#include "Waves/WaveManager.h"

AMyVamSurGameState::AMyVamSurGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyVamSurGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateGameTime();
}

void AMyVamSurGameState::SetWaveManager(const AWaveManager* InWaveManager)
{
	WaveManager = InWaveManager;
}

float AMyVamSurGameState::GetGameTime() const
{
	return GameTime;
}

int AMyVamSurGameState::GetCurrentWaveNumber() const
{
	return WaveManager->GetCurrentWaveNumber();
}

float AMyVamSurGameState::GetTimeUntilNextWave() const
{
	return WaveManager->GetTimeUntilNextWave();
}

void AMyVamSurGameState::UpdateGameTime()
{
	GameTime = GetWorld()->GetTimeSeconds();
	OnGameTimeChanged.Broadcast(GameTime);
}
