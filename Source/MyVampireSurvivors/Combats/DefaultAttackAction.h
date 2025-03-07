// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ICombatAction.h"

class AEnemy;

 /**
  * Represents a default attack action in the game.
  *
  * This class encapsulates the logic for executing a basic attack action, including
  * tracking the instigator (attacker), checking a type(enemy) of a victim, and
  * applying damage to the victim.
  */
class MYVAMPIRESURVIVORS_API FDefaultAttackAction : public ICombatAction
{
public:
	FDefaultAttackAction(const AActor* InInstigator, const int InDamage);

	//~ICombatAction interface
	virtual void ExecuteAction(AActor* Victim) const override;
	virtual const AActor* GetInstigator() const override;
	//~End of ICombatAction interface

private:
	TWeakObjectPtr<const AActor> Instigator;
	const int Damage;

private:
	AController* GetInstigatorController() const;
};
