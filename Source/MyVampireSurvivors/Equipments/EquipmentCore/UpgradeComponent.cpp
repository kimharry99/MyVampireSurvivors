// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeComponent.h"

UUpgradeComponent::UUpgradeComponent()
	: Super()
{
	PrimaryComponentTick.bCanEverTick = false;
}

TArray<UUpgradeOption*> UUpgradeComponent::GetUpgradeableOptions() const
{
	// Empty implementation
	return TArray<UUpgradeOption*>();
}

void UUpgradeComponent::UpgradeStat(UStatComponent* StatComponent, UUpgradeOption* UpgradeOption)
{
	// Empty implementation
}

void UUpgradeComponent::UpdateStat(UStatComponent* StatComponent) const
{
	// Empty implementation
}
