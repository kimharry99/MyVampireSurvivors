// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UI/IDisplableObject.h"
#include "Rewards/Reward.h"
#include "EmptyReward.generated.h"

UCLASS()
class MYVAMPIRESURVIVORS_API UEmptyDisplableObject : public UObject, public IDisplableObject
{
	GENERATED_BODY()

public:
	//~IDisplableObject interface
	virtual const FText GetObjectName() const override;
	virtual const FText GetDescription() const override;
	virtual const UPaperSprite* GetIcon() const override;
	//~End of IDisplableObject interface
};

/**
 * 
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UEmptyReward : public UReward
{
	GENERATED_BODY()

public:
	UEmptyReward();

public:
	//~UReward interface
	virtual void ApplyReward(APlayerCharacter* PlayerCharacter) const override;
	//~End of UReward interface

private:
	//~UReward interface
	virtual void SetRewardData(TScriptInterface<IDisplableObject> NewRewardData) override;
	//~End of UReward interface
};
