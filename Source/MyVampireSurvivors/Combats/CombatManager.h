// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class ICombatAction;
struct FCollisionQueryInfo;

/**
 * 
 */
class MYVAMPIRESURVIVORS_API FCombatManager
{
private:
	FCombatManager() = default;

public:
	static void PerformTargetedAttack(AActor* Target, const ICombatAction& Action);
	static void PerformAoEAttack(const FCollisionQueryInfo& Info, const ICombatAction& Action);

private:
	static TArray<AActor*> FindOverlappedActors(const FCollisionQueryInfo& Info, const AActor* Instigator);
};
