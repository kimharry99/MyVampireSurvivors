// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wave.generated.h"

class AEnemy;
class ASpawner;
class AWave;
class IWaveParticipantInterface;
struct FWaveActorsToSpawn;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWaveCleared, AWave*, ClearedWave);

UCLASS(ClassGroup = "Wave")
class MYVAMPIRESURVIVORS_API AWave : public AActor
{
	GENERATED_BODY()

public:
	AWave(const FObjectInitializer& ObjectInitializer);

public:
	void Trigger(const TArray<FWaveActorsToSpawn>& WaveSpawningActors);

	/** Delegate that is broadcasted when the wave is cleared. */
	FOnWaveCleared OnWaveCleared;

private:
	virtual ASpawner* FindSpawner() const;

	TSet<TWeakObjectPtr<AActor>> SpawnedActors;
	TSet<IWaveParticipantInterface*> SpawnedWaveActors;

	UFUNCTION()
	void HandleSpawnActorDestroyed(AEnemy* Actor);

	void HandleWaveActorDestroyed(IWaveParticipantInterface* WaveActor);

	void ClearWave();
};
