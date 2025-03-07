// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentAbilityNodeDefinition.h"

//////////////////////////////////////////////////////////////////////
// UEquipmentAbilityNodeDefinition
TArray<const UEquipmentAbilityNodeDefinition*> UEquipmentAbilityNodeDefinition::GetChildren() const
{
	return ChildNodes;
}
