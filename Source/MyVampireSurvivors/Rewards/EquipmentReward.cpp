// Fill out your copyright notice in the Description page of Project Settings.


#include "Rewards/EquipmentReward.h"

#include "Players/PlayerCharacter.h"
#include "Rewards/EquipmentRewardData.h"

void UEquipmentReward::ApplyReward(APlayerCharacter* PlayerCharacter) const
{
	PlayerCharacter->EquipEquipment(GetRewardData()->EquipmentClass);
}

const UEquipmentRewardData* UEquipmentReward::GetRewardData() const
{
	return Cast<UEquipmentRewardData>(RewardData.GetObject());
}

void UEquipmentReward::SetRewardData(TScriptInterface<IDisplableObject> NewRewardData)
{
	check(NewRewardData.GetObject()->IsA<UEquipmentRewardData>());
	Super::SetRewardData(NewRewardData);
}
