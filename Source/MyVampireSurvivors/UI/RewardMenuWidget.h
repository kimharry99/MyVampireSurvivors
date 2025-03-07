// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MyVamSurMenuWidget.h"
#include "RewardMenuWidget.generated.h"

class UReward;


/**
 * 
 */
UCLASS()
class MYVAMPIRESURVIVORS_API URewardMenuWidget : public UMyVamSurMenuWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void UpdateOptions(const TArray<UReward*>& Options);
};
