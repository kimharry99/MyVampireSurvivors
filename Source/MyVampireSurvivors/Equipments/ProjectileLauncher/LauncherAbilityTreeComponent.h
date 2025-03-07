// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Equipments/EquipmentCore/AbilityTreeComponent.h"
#include "Equipments/EquipmentCore/NodeVisitor.h"
#include "LauncherAbilityTreeComponent.generated.h"

/**
 *
 */
UCLASS()
class MYVAMPIRESURVIVORS_API ULauncherAbilityTreeComponent : public UAbilityTreeComponent
{
	GENERATED_BODY()

public:
	ULauncherAbilityTreeComponent();

public:
	//~UUpgradeComponent interface
	virtual void UpdateStat(UStatComponent* StatComponent) const override;
	//~End of UUpgradeComponent interface

private:
	class MYVAMPIRESURVIVORS_API FLauncherStatusUpgradingVisitor : public FNodeVisitor
	{
	public:
		FLauncherStatusUpgradingVisitor(UStatComponent* InTargetStatComponent);

		virtual void Process(UAbilityTreeNode* Node) override;
		virtual bool IsVisitable(UAbilityTreeNode* Node) override;

	private:
		TWeakObjectPtr<UStatComponent> TargetStatComponent;
	};
};
