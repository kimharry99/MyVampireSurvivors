// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorPool.generated.h"

class IPoolableActorInterface;

/**
 * AActorPool is a pool manager for reusable Actor instances that implement the IPoolableActorInterface.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API AActorPool : public AActor
{
	GENERATED_BODY()

public:
	AActorPool(const FObjectInitializer& ObjectInitializer);

public:
	AActor* GetPooledActor();

	/**
	 * Sets the Actor class that will be used to spawn pooled actors.
	 *
	 * This method is intended to be called only once during initialization. It performs the following checks:
	 * - Ensures that the ActorClass has not been previously set to prevent runtime changes.
	 * - Validates that the provided NewActorClass is not null.
	 * - Confirms that the NewActorClass implements the IPoolableActorInterface, ensuring compatibility with the pool.
	 *
	 * @param NewActorClass The Actor class to be used for creating poolable actors.
	 */
	void SetActorClass(TSubclassOf<AActor> NewActorClass);

protected:
	//~AActor interface
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~End of AActor interface

private:
	UPROPERTY(Transient)
	TArray<TObjectPtr<AActor>> PooledActors;

	UPROPERTY(EditDefaultsOnly, Category = "Object Pool")
	TSubclassOf<AActor> ActorClass;

	int ExpansionAmount = 5;

	void ReleaseActor(IPoolableActorInterface* ActorToRelease);
	AActor* ExpandPoolAndReturnFirst();
};
