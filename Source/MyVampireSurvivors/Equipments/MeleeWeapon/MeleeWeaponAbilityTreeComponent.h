// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Equipments/EquipmentCore/NodeVisitor.h"
#include "Equipments/EquipmentCore/AbilityTreeComponent.h"
#include "MeleeWeaponAbilityTreeComponent.generated.h"

/**
 * 
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UMeleeWeaponAbilityTreeComponent : public UAbilityTreeComponent
{
	GENERATED_BODY()

public:
	UMeleeWeaponAbilityTreeComponent();

public:
	//~UUpgradeComponent interface
	virtual void UpdateStat(UStatComponent* StatComponent) const;
	//~End of UUpgradeComponent interface

private:
	class MYVAMPIRESURVIVORS_API FMeleeWeaponStatusUpgradingVisitor : public FNodeVisitor
	{
	public:
		FMeleeWeaponStatusUpgradingVisitor(UStatComponent* InTargetStatComponent);
	
	public:
		//~FNodeVisitor interface
		virtual void Process(UAbilityTreeNode* Node) override;
		virtual bool IsVisitable(UAbilityTreeNode* Node) override;
		//~End of FNodeVisitor interface

	private:
		TWeakObjectPtr<UStatComponent> TargetStatComponent;
	};
};
