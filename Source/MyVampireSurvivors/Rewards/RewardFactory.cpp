// Fill out your copyright notice in the Description page of Project Settings.


#include "Rewards/RewardFactory.h"

#include "Equipments/EquipmentCore/UpgradeOption.h"
#include "Rewards/EmptyReward.h"
#include "Rewards/EquipmentReward.h"
#include "Rewards/EquipmentRewardData.h"
#include "Rewards/EquipmentAbilityReward.h"

UReward* FRewardFactory::CreateEmptyReward(UObject* Outer) const
{
	UEmptyReward* Reward = NewObject<UEmptyReward>(Outer);

	return Reward;
}

UReward* FRewardFactory::CreateReward(UObject* Outer, UEquipmentRewardData* RewardData) const
{
	UEquipmentReward* Reward = NewObject<UEquipmentReward>(Outer);
	Reward->SetRewardData(RewardData);

	return Reward;
}

UReward* FRewardFactory::CreateReward(UObject* Outer, UUpgradeOption* UnlockingNode) const
{
	UEquipmentAbilityReward* Reward = NewObject<UEquipmentAbilityReward>(Outer);
	Reward->SetRewardData(UnlockingNode);

	return Reward;
}
