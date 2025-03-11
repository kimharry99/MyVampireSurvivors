// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wave.generated.h"

class ASpawner;
class IWaveParticipantInterface;
struct FWaveActorsToSpawn;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveCleared, AWave*, ClearedWave);

/**
 * AWave is responsible for managing a wave of spawned actors in the game.
 * It handles the spawning of enemies or other wave participants using a Spawner,
 * tracks their lifecycle, and triggers events when the wave is cleared.
*/
UCLASS(ClassGroup = "Wave")
class MYVAMPIRESURVIVORS_API AWave : public AActor
{
	GENERATED_BODY()

public:
	AWave(const FObjectInitializer& ObjectInitializer);

public:
	/**
	 * Triggers the wave by spawning a set of actors as defined in WaveSpawningActors.
	 * Each actor is spawned using the Spawner and tracked if it implements the IWaveParticipantInterface.
	 */
	void Trigger(const TArray<FWaveActorsToSpawn>& WaveSpawningActors);

	/** Delegate that is broadcasted when the wave is cleared. */
	FOnWaveCleared OnWaveCleared;

private:
	virtual ASpawner* FindSpawner() const;

	TSet<IWaveParticipantInterface*> SpawnedWaveActors;

	void HandleWaveActorDestroyed(IWaveParticipantInterface* WaveActor);

	void ClearWave();
};
