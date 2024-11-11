// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentManager.generated.h"

class UEquipmentInventoryComponent;


/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class MYVAMPIRESURVIVORS_API UEquipmentManager : public UObject
{
	GENERATED_BODY()

public:
	void GiveEquipmentReward(UEquipmentInventoryComponent* TargetInventory);

private:
	void AddEquipmentToInventory(UEquipmentInventoryComponent* TargetInventory);
	void UpgradeEquipmentInInventory(UEquipmentInventoryComponent* TargetInventory);
};
