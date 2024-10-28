// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipments/EquipmentInventory.h"
#include "Equipments/EquipmentItem.h"

void FEquipmentInventory::AddEquipment(AEquipmentItem* Equipment)
{
	Equipments.Add(Equipment);
}

TArray<AEquipmentItem*> FEquipmentInventory::GetAllEnableEquipments() const
{
	TArray<AEquipmentItem*> Results;
	for (AEquipmentItem* Equipment : Equipments)
	{
		if (Equipment->IsUsable())
		{
			Results.Add(Equipment);
		}
	}
	return Results;
}

void FEquipmentInventory::UseAllEnableEquipments_Deprecated()
{
	for (AEquipmentItem* Equipment : Equipments)
	{
		if (Equipment->IsUsable())
		{
			Equipment->UseEquipment();
		}
	}
}
