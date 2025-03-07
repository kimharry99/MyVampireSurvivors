// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UObject;

class UUpgradeOption;
class UEquipmentRewardData;
class UReward;

/**
 *
 */
class MYVAMPIRESURVIVORS_API FRewardFactory
{
public:
	UReward* CreateEmptyReward(UObject* Outer) const;
	UReward* CreateReward(UObject* Outer, UEquipmentRewardData* RewardData) const;
	UReward* CreateReward(UObject* Outer, UUpgradeOption* UnlockingNode) const;
};
