// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentManager.generated.h"

class UEquipmentComponent;

/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class MYVAMPIRESURVIVORS_API UEquipmentManager : public UObject
{
	GENERATED_BODY()

public:
	void GiveEquipmentReward(UEquipmentComponent* TargetInventory);

private:
	void AddEquipmentToInventory(UEquipmentComponent* TargetInventory);
	void UpgradeEquipmentInInventory(UEquipmentComponent* TargetInventory);
};
