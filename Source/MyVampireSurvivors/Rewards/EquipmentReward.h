// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Rewards/Reward.h"
#include "EquipmentReward.generated.h"

class UEquipmentRewardData;

/**
 * 
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UEquipmentReward : public UReward
{
	GENERATED_BODY()

public:
	//~UReward interface
	virtual void ApplyReward(APlayerCharacter* PlayerCharacter) const override;
	virtual void SetRewardData(TScriptInterface<IDisplableObject> NewRewardData) override;
	//~End of UReward interface

public:
	UFUNCTION(BlueprintCallable)
	const UEquipmentRewardData* GetRewardData() const;
};
