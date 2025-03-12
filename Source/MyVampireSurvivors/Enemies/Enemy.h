// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Characters/MyVamSurCharacter.h"
#include "Waves/WaveParticipantInterface.h"
#include "ObjectPools/PoolableActorInterface.h"
#include "Enemy.generated.h"

template <class TClass> class TSubclassOf;

class AEnemy;
class APickableItem;
class ASpawner;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDied, AEnemy*, DiedEnemy);

/**
 * The base class for all enemies in the game.
 *
 * Chase the player by default.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API AEnemy : public AMyVamSurCharacter, public IPoolableActorInterface, public IWaveParticipantInterface
{
	GENERATED_BODY()

public:
	AEnemy();

public:
	//~IPoolableActorInterface interface
	virtual void ActivateFromPool() override;
	virtual void DeactivateToPool() override;
	virtual FReturnToPoolDelegate* GetReturnToPoolDelegate() override;
	virtual bool IsInUse() const override;
	//~End of IPoolableActorInterface interface

	void CopyFromActualClass(TSubclassOf<AEnemy> ActualClass);

protected:
	//~AActor interface
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	//~End of AActor interface

	//~AMyVamSurCharacter interface
	virtual void StartDeath() override;
	//~End of AMyVamSurCharacter interface

	//~IWaveParticipantInterface interface
	virtual FOnWaveActorDestroyedDelegate* GetOnWaveActorDestroyedDelegate() override;
	//~End of IWaveParticipantInterface interface

public:
	FReturnToPoolDelegate OnReturnToPool;
	FOnEnemyDied OnEnemyDied;
	FOnWaveActorDestroyedDelegate OnWaveActorDestroyed;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
	TSubclassOf<APickableItem> DropItemClass;

	void SpawnDropItem();

	UPROPERTY(Transient)
	TObjectPtr<ASpawner> DropItemSpawner;

	bool bIsInUse;
};
