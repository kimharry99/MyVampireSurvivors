// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IMeleeWeaponStats.generated.h"

class UPaperFlipbook;
struct FEquipmentAnimationData;

UINTERFACE(MinimalAPI)
class UMeleeWeaponStats : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class MYVAMPIRESURVIVORS_API IMeleeWeaponStats
{
	GENERATED_BODY()

public:
	virtual int GetDamage() const = 0;
	virtual void AddDamage(int Value) = 0;
	virtual void AddDamageMultiplier(float Value) = 0;

	virtual float GetCooldown() const = 0;
	virtual void AddAttackSpeed(float Value) = 0;
	virtual void AddAttackSpeedMultiplier(float Value) = 0;
	
	virtual FVector GetHitboxExtent() const = 0;
	virtual FVector GetHitboxOffset() const = 0;

	virtual void AddAttackRangeMultiplier(float Value) = 0;
};
