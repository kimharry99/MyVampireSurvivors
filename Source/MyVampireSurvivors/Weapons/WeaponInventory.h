// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "WeaponInventory.generated.h"

/**
 * Container of weapons equipped by the player.
 */
USTRUCT()
struct MYVAMPIRESURVIVORS_API FWeaponInventory
{
	GENERATED_BODY()

public:
	/**
	 * Add a weapon to inventory.
	 *
	 * @param Weapon Weapon to equip.
	 */
	void AddWeapon(AWeapon* Weapon);

	/**
	 * Use all enabled weapons in inventory.
	 */
	void UseAllEnableWeapons();

private:
	/** The array of Equipped weapons. */
	UPROPERTY()
	TArray<TObjectPtr<AWeapon>> EquippedWeapons;
};
