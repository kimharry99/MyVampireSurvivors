// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Rewards/Reward.h"
#include "EquipmentAbilityReward.generated.h"

class UUpgradeOption;

/**
 * 
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UEquipmentAbilityReward : public UReward
{
	GENERATED_BODY()

public:
	//~UReward interface
	virtual void ApplyReward(APlayerCharacter* PlayerCharacter) const override;
	virtual void SetRewardData(TScriptInterface<IDisplableObject> NewRewardData) override;
	//~End of UReward interface

	UUpgradeOption* GetAbilityRewardData() const;
};
