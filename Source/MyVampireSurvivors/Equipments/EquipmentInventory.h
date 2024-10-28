// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentInventory.generated.h"

class AEquipmentItem;

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
	void AddEquipment(AEquipmentItem* Equipment);

	/**
	 * Returns all enable equipments in inventory.
	 */
	TArray<AEquipmentItem*> GetAllEnableEquipments() const;

	/**
	 * Use all usable equipments in inventory.
	 */
	void UseAllEnableEquipments_Deprecated();

private:
	/** The array of equipments. */
	UPROPERTY()
	TArray<TObjectPtr<AEquipmentItem>> Equipments;
};
