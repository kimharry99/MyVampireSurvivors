// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment.h"
#include "EquipmentInventory.generated.h"

/**
 * Container of equipments for the player.
 */
USTRUCT()
struct MYVAMPIRESURVIVORS_API FEquipmentInventory
{
	GENERATED_BODY()

public:
	/**
	 * Add a equipment to inventory.
	 */
	void AddEquipment(AEquipment* Equipment);

	/**
	 * Use all usable equipments in inventory.
	 */
	void UseAllEnableEquipments();

private:
	/** The array of equipments. */
	UPROPERTY()
	TArray<TObjectPtr<AEquipment>> Equipments;
};
