// Fill out your copyright notice in the Description page of Project Settings.


#include "Rewards/Reward.h"

#include "Items/ItemDefinition.h"

void UReward::ApplyReward(APlayerCharacter* PlayerCharacter) const
{
	// Default implementation does nothing.
}

const FText UReward::GetObjectName() const
{
	return RewardData->GetObjectName();
}

const FText UReward::GetDescription() const
{
	return RewardData->GetDescription();
}

const UPaperSprite* UReward::GetIcon() const
{
	return RewardData->GetIcon();
}

void UReward::SetRewardData(TScriptInterface<IDisplableObject> NewRewardData)
{
	check(NewRewardData.GetObject());
	RewardData = NewRewardData;
}
