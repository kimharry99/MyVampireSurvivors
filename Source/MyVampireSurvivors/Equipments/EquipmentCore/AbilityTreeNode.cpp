// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTreeNode.h"

#include "Equipment.h"
#include "Equipments/EquipmentData/EquipmentAbilityNodeDefinition.h"

//////////////////////////////////////////////////////////////////////
// UAbilityTreeNode
const FText UAbilityTreeNode::GetObjectName() const
{
	return NodeDefinition ? NodeDefinition->Name : FText();
}

const FText UAbilityTreeNode::GetDescription() const
{
	return NodeDefinition ? NodeDefinition->Description : FText();
}

const UPaperSprite* UAbilityTreeNode::GetIcon() const
{
	return NodeDefinition ? NodeDefinition->Icon : nullptr;
}

bool UAbilityTreeNode::IsActive() const
{
	return bIsActive;
}

AEquipment* UAbilityTreeNode::GetOwningEquipment() const
{
	return OwingEquipment.Get();
}

void UAbilityTreeNode::Activate()
{
	bIsActive = true;
}

void UAbilityTreeNode::SetOwingEquipment(AEquipment* NewOwingEquipment)
{
	if (OwingEquipment.Get() == NewOwingEquipment)
	{
		return;
	}

	OwingEquipment = NewOwingEquipment;
}

void UAbilityTreeNode::SetNodeDefinition(const UEquipmentAbilityNodeDefinition* NewNodeDefinition)
{
	if (NodeDefinition == NewNodeDefinition)
	{
		return;
	}

	NodeDefinition = NewNodeDefinition;
}

TArray<const UAbilityTreeNode*> UAbilityTreeNode::GetChildren() const
{
	TArray<const UAbilityTreeNode*> Result;
	for (const UAbilityTreeNode* ChildNode : ChildNodes)
	{
		Result.Add(ChildNode);
	}
	return Result;
}

TArray<UAbilityTreeNode*> UAbilityTreeNode::GetChildren()
{
	return ChildNodes;
}

void UAbilityTreeNode::AddChildNode(UAbilityTreeNode* ChildNode)
{
	if (ChildNode)
	{
		ChildNodes.Add(ChildNode);
	}
}
