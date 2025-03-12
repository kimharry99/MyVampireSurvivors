// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

class AEnemy;
class AActorPool;

/**
 * EnemySpanwer spawns enemies at random locations.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API ASpawner : public AActor
{
	GENERATED_BODY()

public:
	/**
	 * Spawn an actor at random location in spawn boundary.
	 *
	 * @param ActorClass - Actor class to spawn
	 * @return Spawned actor
	 */
	AActor* SpawnActorAtRandomInMap(TSubclassOf<AActor> ActorClass);
	AActor* SpawnActor(TSubclassOf<AActor> ActorClass, const FTransform& SpawnTransform);

protected:
	//~AActor interface
	virtual void BeginPlay() override;
	//~End of AActor interface

private:
	/** Boundary of spawn area */
	FBox SpawnBoundary = FBox();

	UPROPERTY(VisibleAnywhere, Category = "Enemy")
	TObjectPtr<AActorPool> EnemyPool;

	void InitializeEnemyPool();

	AActor* SpawnActorByType(TSubclassOf<AActor> ActorClass);
	AEnemy* SpawnEnemy(TSubclassOf<AEnemy> EnemyClass);
};
