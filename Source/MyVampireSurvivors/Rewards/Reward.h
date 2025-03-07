// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Reward.generated.h"

class UItemDefinition;
class IDisplableObject;
class APlayerCharacter;

/**
 * 
 */
UCLASS(Abstract, BlueprintType)
class MYVAMPIRESURVIVORS_API UReward : public UObject
{
	GENERATED_BODY()

public:
	virtual void ApplyReward(APlayerCharacter* PlayerCharacter) const;

protected:
	UPROPERTY()
	TScriptInterface<IDisplableObject> RewardData;

public:
	UFUNCTION(BlueprintCallable)
	const FText GetObjectName() const;

	UFUNCTION(BlueprintCallable)
	const FText GetDescription() const;

	UFUNCTION(BlueprintCallable)
	const UPaperSprite* GetIcon() const;

	virtual void SetRewardData(TScriptInterface<IDisplableObject> NewRewardData);
};
