// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "AutoWeaponInventory.generated.h"

/**
 * 
 */
USTRUCT()
struct MYVAMPIRESURVIVORS_API FAutoWeaponInventory
{
	GENERATED_BODY()

public:
	/**
	 * Add a weapon to inventory.
	 * 
	 * @param Weapon Weapon to equip.
	 */
	void AddWeapon(AWeapon* Weapon);

private:
	/** The array of Equipped weapons. */
	UPROPERTY()
	TArray<TObjectPtr<AWeapon>> EquippedWeapons;
};
