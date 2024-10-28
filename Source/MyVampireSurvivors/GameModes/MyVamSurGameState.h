// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyVamSurGameState.generated.h"

class AWaveManager;

UCLASS()
class MYVAMPIRESURVIVORS_API AMyVamSurGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	void SetWaveManager(const AWaveManager* InWaveManager);

	int GetCurrentWaveNumber() const;
	float GetTimeUntilNextWave() const;

private:
	UPROPERTY()
	TObjectPtr<const AWaveManager> WaveManager;
};
