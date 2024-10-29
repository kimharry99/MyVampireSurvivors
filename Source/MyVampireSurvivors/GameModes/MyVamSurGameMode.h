// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Waves/WaveManager.h"
#include "MyVamSurGameMode.generated.h"

class UToroidalWorldSystem;

/**
 * 
 */
UCLASS()
class MYVAMPIRESURVIVORS_API AMyVamSurGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyVamSurGameMode();

protected:
	//~AGameModeBase interface
	virtual void PreInitializeComponents() override;
	//~End of AGameModeBase interface

public:
	/**
	 * Returns the toroidal world system.
	 */
	UToroidalWorldSystem* GetToroidalWorldSystem() const;

private:
	UPROPERTY()
	TObjectPtr<UToroidalWorldSystem> ToroidalWorldSystem;

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	TSubclassOf<AWaveManager> WaveManagerClass;

	UPROPERTY()
	TObjectPtr<AWaveManager> WaveManager;

private:
	/**
	 * Add the toroidal world system to the game.
	 */
	void AddToroidalWorldSystemToGame();

	/**
	 * Add the wave manager to the game.
	 * Spawn the wave manager actor.
	 */
	void AddWaveManagerToGame();
};