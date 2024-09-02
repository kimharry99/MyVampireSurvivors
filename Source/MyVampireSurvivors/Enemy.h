// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Enemy.generated.h"

/**
 * The base class for all enemies in the game.
 * 
 * Chase the player by default.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API AEnemy : public APaperCharacter
{
	GENERATED_BODY()

public:
	AEnemy();

protected:
	virtual void BeginPlay() override;

	/**
	 * Kill the enemy.
	 */
	virtual void TriggerDeath();

private:
	/**
	 * FIXME: Temporary implementation.
	 * Handle for the death timer.
	 */
	FTimerHandle DeathHandle;
};
