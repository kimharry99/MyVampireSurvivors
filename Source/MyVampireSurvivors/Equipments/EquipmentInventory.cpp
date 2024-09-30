// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipments/EquipmentInventory.h"

void FEquipmentInventory::AddEquipment(AEquipment* Equipment)
{
	Equipments.Add(Equipment);
}

void FEquipmentInventory::UseAllEnableEquipments()
{
	for (AEquipment* Equipment : Equipments)
	{
		if (Equipment->IsUsable())
		{
			Equipment->UseEquipment();
		}
	}
}
