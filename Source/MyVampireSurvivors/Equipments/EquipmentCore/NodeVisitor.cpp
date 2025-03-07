// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeVisitor.h"

#include "AbilityTreeNode.h"

//////////////////////////////////////////////////////////////////////
// FUpgradeableNodeCollectingVisitor
void FUpgradeableNodeCollectingVisitor::Process(UAbilityTreeNode* Node)
{
	if (Node && Node->IsActive())
	{
		for (UAbilityTreeNode* ChildNode : Node->GetChildren())
		{
			if (ChildNode && !ChildNode->IsActive())
			{
				UpgradeableNodes.Add(ChildNode);
			}
		}
	}
}

bool FUpgradeableNodeCollectingVisitor::IsVisitable(UAbilityTreeNode* Node)
{
	return Node ? Node->IsActive() : false;
}

TArray<UAbilityTreeNode*> FUpgradeableNodeCollectingVisitor::GetUpgradeableNodes() const
{
	return UpgradeableNodes;
}
