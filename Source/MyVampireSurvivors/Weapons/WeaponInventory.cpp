// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/WeaponInventory.h"

void FWeaponInventory::AddWeapon(AWeapon* Weapon)
{
	EquippedWeapons.Add(Weapon);
}

void FWeaponInventory::UseAllEnableWeapons()
{
	for (AWeapon* Weapon : EquippedWeapons)
	{
		if (Weapon->IsUsable())
		{
			Weapon->UseWeapon();
		}
	}
}
