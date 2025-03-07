// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UpgradeComponent.h"
#include "AbilityTreeComponent.generated.h"

class FNodeVisitor;
class UAbilityTreeNode;
class UEquipmentAbilityNodeDefinition;
class UStatComponent;
class UUpgradeOption;

/**
 *
 */
UCLASS(Abstract)
class MYVAMPIRESURVIVORS_API UAbilityTreeComponent : public UUpgradeComponent
{
	GENERATED_BODY()

protected:
	UAbilityTreeComponent();

public:
	//~UUpgradeComponent interface
	virtual TArray<UUpgradeOption*> GetUpgradeableOptions() const override;
	virtual void UpgradeStat(UStatComponent* StatComponent, UUpgradeOption* UpgradeOption) override;
	//~End of UUpgradeComponent interface
	
protected:
	//~UActorComponent interface
	virtual void BeginPlay() override;
	//~End of UActorComponent interface

	/**
	 * Traverses the entire ability tree using the given visitor.
	 * @param Visitor The visitor used to process nodes.
	 */
	void TraverseTree(FNodeVisitor& Visitor) const;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	TObjectPtr<UEquipmentAbilityNodeDefinition> RootNodeDefinition;

	UPROPERTY()
	TObjectPtr<UAbilityTreeNode> Root = nullptr;

private:
	/**
	 * Initializes the ability tree by creating the root and unlocking it.
	 */
	void InitializeTree();

	/**
	 * Creates the ability tree from the root node definition.
	 * @return The root node of the ability tree.
	 */
	UAbilityTreeNode* CreateTree();

	/**
	 * Recursively creates nodes in the ability tree based on the given definition.
	 * Prevents cycles by tracking visited definitions.
	 * @param CurrentDefinition The definition for the current node.
	 * @param Visited A set of already visited definitions.
	 * @return The newly created ability tree node, or nullptr on failure.
	 */
	UAbilityTreeNode* CreateTreeFromDefinition(const UEquipmentAbilityNodeDefinition* CurrentDefinition, TSet<const UEquipmentAbilityNodeDefinition*>& Visited);
};
