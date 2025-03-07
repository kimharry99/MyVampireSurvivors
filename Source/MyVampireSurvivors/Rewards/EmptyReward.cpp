// Fill out your copyright notice in the Description page of Project Settings.


#include "Rewards/EmptyReward.h"

//////////////////////////////////////////////////////////////////////
// UEmptyDisplableObject
const FText UEmptyDisplableObject::GetObjectName() const
{
	return FText();
}

const FText UEmptyDisplableObject::GetDescription() const
{
	return FText();
}

const UPaperSprite* UEmptyDisplableObject::GetIcon() const
{
	return nullptr;
}

//////////////////////////////////////////////////////////////////////
// UEmptyReward
UEmptyReward::UEmptyReward()
{
	// Set the reward data to an empty object
	UEmptyDisplableObject* EmptyDisplableObject = CreateDefaultSubobject<UEmptyDisplableObject>(TEXT("EmptyDisplableObject"));
	SetRewardData(EmptyDisplableObject);
}

void UEmptyReward::ApplyReward(APlayerCharacter* PlayerCharacter) const
{
	Super::ApplyReward(PlayerCharacter);

	// Do nothing
}

void UEmptyReward::SetRewardData(TScriptInterface<IDisplableObject> NewRewardData)
{
	Super::SetRewardData(NewRewardData);

	// Do nothing
}
