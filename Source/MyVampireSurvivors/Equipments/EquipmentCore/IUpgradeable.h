// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IUpgradeable.generated.h"

class UUpgradeOption;

UINTERFACE(MinimalAPI)
class UUpgradeable : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class MYVAMPIRESURVIVORS_API IUpgradeable
{
	GENERATED_BODY()

public:
	virtual void GetUpgradeableOptions(OUT TArray<UUpgradeOption*>& OutOptions) const = 0;
	virtual void Upgrade(UUpgradeOption * UpgradeOption) = 0;
};
