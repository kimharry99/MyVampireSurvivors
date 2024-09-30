// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enemies/Enemy.h"
#include "WeaponInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWeaponInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for weapons which attack enemies.
 */
class MYVAMPIRESURVIVORS_API IWeaponInterface
{
	GENERATED_BODY()

public:
	/**
	 * Attack an enemy.
	 *
	 * @param AttackedEnemy The enemy to attack.
	 */
	virtual void AttackEnemy(AEnemy* AttackedEnemy);

protected:
	/**
	 * Returns the controller of the weapon, or nullptr if the weapon has no controller.
	 */
	virtual AController* GetController() const = 0;

	/**
	 * Returns the damage of the weapon.
	 */
	virtual float GetWeaponDamage() const = 0;
};
