// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UAbilityTreeNode;

/**
 * 
 */
class MYVAMPIRESURVIVORS_API FNodeVisitor
{
public:
	FNodeVisitor() = default;
	virtual ~FNodeVisitor() = default;

	virtual void Process(UAbilityTreeNode* Node) = 0;
	virtual bool IsVisitable(UAbilityTreeNode* Node) = 0;
};

/**
 *
 */
class MYVAMPIRESURVIVORS_API FUpgradeableNodeCollectingVisitor : public FNodeVisitor
{
public:
	virtual void Process(UAbilityTreeNode* Node) override;
	virtual bool IsVisitable(UAbilityTreeNode* Node) override;

	TArray<UAbilityTreeNode*> GetUpgradeableNodes() const;

private:
	TArray<UAbilityTreeNode*> UpgradeableNodes;
};
