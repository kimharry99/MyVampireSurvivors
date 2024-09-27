// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/AutoWeaponInventory.h"

void FAutoWeaponInventory::AddWeapon(AWeapon* Weapon)
{
	EquippedWeapons.Add(Weapon);
}
