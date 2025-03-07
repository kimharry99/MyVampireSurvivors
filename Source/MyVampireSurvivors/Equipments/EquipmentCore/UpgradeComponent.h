// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UpgradeComponent.generated.h"

class UStatComponent;
class UUpgradeOption;

UCLASS(ClassGroup = Equipment, Abstract)
class MYVAMPIRESURVIVORS_API UUpgradeComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UUpgradeComponent();

public:
	virtual TArray<UUpgradeOption*> GetUpgradeableOptions() const;
	virtual void UpgradeStat(UStatComponent* StatComponent, UUpgradeOption* UpgradeOption);
	virtual void UpdateStat(UStatComponent* StatComponent) const;
};
