// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class AActor;

/**
 * 
 */
class MYVAMPIRESURVIVORS_API ICombatAction
{
public:
	virtual ~ICombatAction();
	virtual void ExecuteAction(AActor* Victim) const = 0;

	virtual const AActor* GetInstigator() const = 0;
};
