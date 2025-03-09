// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Characters/MyVamSurCharacter.h"
#include "Enemy.generated.h"

template <class TClass> class TSubclassOf;

class AEnemy;
class APickableItem;
class UToroidalNPAComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDied, AEnemy*, DiedEnemy);

/**
 * The base class for all enemies in the game.
 * 
 * Chase the player by default.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API AEnemy : public AMyVamSurCharacter
{
	GENERATED_BODY()

public:
	AEnemy();

protected:
	//~AActor interface
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	//~End of AActor interface

	//~AMyVamSurCharacter interface
	virtual void StartDeath() override;
	//~End of AMyVamSurCharacter interface

public:
	FOnEnemyDied OnEnemyDied;

private:
	UPROPERTY(EditDefaultsOnly, Category="Enemy")
	TSubclassOf<APickableItem> DropItemClass;

private:
	void SpawnDropItem();
};
