// Fill out your copyright notice in the Description page of Project Settings.


#include "Rewards/EquipmentAbilityReward.h"

#include "Equipments/EquipmentCore/UpgradeOption.h"
#include "Equipments/EquipmentCore/Equipment.h"
#include "Players/PlayerCharacter.h"

void UEquipmentAbilityReward::ApplyReward(APlayerCharacter* PlayerCharacter) const
{
	Super::ApplyReward(PlayerCharacter);

	if (UUpgradeOption* UnlockingOption = GetAbilityRewardData())
	{
		if (AEquipment* UpgradingEquipment = UnlockingOption->GetOwningEquipment())
		{
			UpgradingEquipment->Upgrade(UnlockingOption);
		}
	}
}

void UEquipmentAbilityReward::SetRewardData(TScriptInterface<IDisplableObject> NewRewardData)
{
	Super::SetRewardData(NewRewardData);
}

UUpgradeOption* UEquipmentAbilityReward::GetAbilityRewardData() const
{
	return Cast<UUpgradeOption>(RewardData.GetObject());
}
