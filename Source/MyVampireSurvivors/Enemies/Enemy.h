// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/MyVamSurCharacter.h"
#include "Enemy.generated.h"

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
	virtual void BeginPlay() override;
	//~End of AActor interface

	//~AMyVamSurCharacter interface
	virtual void Die() override;
	//~End of AMyVamSurCharacter interface
};
