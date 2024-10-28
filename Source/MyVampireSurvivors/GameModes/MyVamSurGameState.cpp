// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/MyVamSurGameState.h"
#include "Waves/WaveManager.h"

void AMyVamSurGameState::SetWaveManager(const AWaveManager* InWaveManager)
{
	WaveManager = InWaveManager;
}

int AMyVamSurGameState::GetCurrentWaveNumber() const
{
	return WaveManager->GetCurrentWaveNumber();
}

float AMyVamSurGameState::GetTimeUntilNextWave() const
{
	return WaveManager->GetTimeUntilNextWave();
}
