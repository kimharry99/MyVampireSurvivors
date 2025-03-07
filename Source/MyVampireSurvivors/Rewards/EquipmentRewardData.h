// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Items/ItemDefinition.h"
#include "EquipmentRewardData.generated.h"

class AEquipment;

/**
 * 
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UEquipmentRewardData : public UItemDefinition
{
	GENERATED_BODY()

public:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TSubclassOf<AEquipment> EquipmentClass;
};
