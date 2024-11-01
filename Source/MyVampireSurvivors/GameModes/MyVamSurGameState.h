// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyVamSurGameState.generated.h"

class AWaveManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameTimeChanged, double, NewGameTime);

UCLASS()
class MYVAMPIRESURVIVORS_API AMyVamSurGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AMyVamSurGameState();

protected:
	//~AActor interface
	virtual void Tick(float DeltaSeconds) override;
	//~End of AActor interface

public:
	void SetWaveManager(const AWaveManager* InWaveManager);

	int GetCurrentWaveNumber() const;
	float GetTimeUntilNextWave() const;

	float GetGameTime() const;

	FOnGameTimeChanged OnGameTimeChanged;

private:
	float GameTime = -1.0f;

	UPROPERTY()
	TObjectPtr<const AWaveManager> WaveManager;

private:
	void UpdateGameTime();
};
