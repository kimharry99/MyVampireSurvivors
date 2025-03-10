// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

template <class TClass> class TSubclassOf;
class AEnemy;

/**
 * EnemySpanwer spawns enemies at random locations.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API ASpawner : public AActor
{
	GENERATED_BODY()

public:
	/**
	 * Spawn an enemy at random location in spawn boundary.
	 *
	 * @param EnemyClass - Enemy class to spawn
	 * @return Spawned enemy
	 */
	AEnemy* SpawnEnemy(TSubclassOf<AEnemy> EnemyClass) const;

	/**
	 * Spawn an actor at random location in spawn boundary.
	 *
	 * @param ActorClass - Actor class to spawn
	 * @return Spawned actor
	 */
	AActor* SpawnActorAtRandomInMap(TSubclassOf<AActor> ActorClass);

protected:
	virtual void BeginPlay() override;

private:
	/** Boundary of spawn area */
	FBox SpawnBoundary = FBox();
};
