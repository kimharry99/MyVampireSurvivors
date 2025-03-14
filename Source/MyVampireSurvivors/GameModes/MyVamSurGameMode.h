// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyVamSurGameMode.generated.h"

template <class TClass> class TSubclassOf;

class ASpawner;
class AWaveManager;
class URewardManager;
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

	ASpawner* GetSpawner() const;

	URewardManager* GetRewardManager() const;

private:
	UPROPERTY()
	TObjectPtr<UToroidalWorldSystem> ToroidalWorldSystem;

	UPROPERTY()
	TObjectPtr<ASpawner> Spawner;

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	TSubclassOf<AWaveManager> WaveManagerClass;

	UPROPERTY()
	TObjectPtr<AWaveManager> WaveManager;

	UPROPERTY(EditDefaultsOnly, Category = "Classes")
	TSubclassOf<URewardManager> RewardManagerClass;

	UPROPERTY()
	TObjectPtr<URewardManager> RewardManager;

private:
	/**
	 * Add the toroidal world system to the game.
	 */
	void AddToroidalWorldSystemToGame();

	void AddSpawnerToGame();

	/**
	 * Add the wave manager to the game.
	 * Spawn the wave manager actor.
	 */
	void AddWaveManagerToGame();

	void CreateRewardManager();
};
