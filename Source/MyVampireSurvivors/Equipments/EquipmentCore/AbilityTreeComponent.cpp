// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTreeComponent.h"

#include "Equipment.h"
#include "Equipments/EquipmentData/EquipmentAbilityNodeDefinition.h"
#include "MyVamSurLogChannels.h"
#include "AbilityTreeNode.h"
#include "NodeVisitor.h"

static const int MAX_TRAVERSAL_DEPTH = 1000;

namespace
{
	/**
	 * Recursively traverses nodes in the ability tree.
	 * Processes each node with the provided visitor, and enforces a maximum depth limit.
	 * @param CurrentNode The current node to process.
	 * @param Visitor The visitor that processes nodes.
	 * @param CurrentDepth The current depth of the traversal.
	 */
	void TraverseNodesInternal(UAbilityTreeNode* CurrentNode, FNodeVisitor& Visitor, int CurrentDepth)
	{
		if (CurrentDepth > MAX_TRAVERSAL_DEPTH)
		{
			UE_LOG(LogMyVamSur, Warning, TEXT("Traversal depth exceeded the limit of %d"), MAX_TRAVERSAL_DEPTH);
			return;
		}
		if (!CurrentNode || !Visitor.IsVisitable(CurrentNode))
		{
			return;
		}

		Visitor.Process(CurrentNode);

		for (UAbilityTreeNode* ChildNode : CurrentNode->GetChildren())
		{
			TraverseNodesInternal(ChildNode, Visitor, CurrentDepth + 1);
		}
	}
}

//////////////////////////////////////////////////////////////////////
// UAbilityTreeComponent
UAbilityTreeComponent::UAbilityTreeComponent()
	: Super()
{
}

TArray<UUpgradeOption*> UAbilityTreeComponent::GetUpgradeableOptions() const
{
	FUpgradeableNodeCollectingVisitor Visitor;
	TraverseTree(Visitor);

	TArray<UUpgradeOption*> Result;
	for (UAbilityTreeNode* Node : Visitor.GetUpgradeableNodes())
	{
		Result.Add(Node);
	}

	return Result;
}

void UAbilityTreeComponent::UpgradeStat(UStatComponent* StatComponent, UUpgradeOption* UpgradeOption)
{
	Super::UpgradeStat(StatComponent, UpgradeOption);

	if (UAbilityTreeNode* UpgradeNode = Cast<UAbilityTreeNode>(UpgradeOption))
	{
		UpgradeNode->Activate();
	}

	UpdateStat(StatComponent);
}

void UAbilityTreeComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeTree();
}

void UAbilityTreeComponent::TraverseTree(FNodeVisitor& Visitor) const
{
	TraverseNodesInternal(Root, Visitor, 0);
}

void UAbilityTreeComponent::InitializeTree()
{
	Root = CreateTree();
	if (Root)
	{
		Root->Activate();
	}
}

UAbilityTreeNode* UAbilityTreeComponent::CreateTree()
{
	UE_CLOG(!RootNodeDefinition, LogMyVamSur, Warning, TEXT("RootNodeDefinition is not set in AbilityTreeComponent of Equipment %s"), *(GetOwner()->GetName()));

	TSet<const UEquipmentAbilityNodeDefinition*> Visited;
	return CreateTreeFromDefinition(RootNodeDefinition, Visited);
}

UAbilityTreeNode* UAbilityTreeComponent::CreateTreeFromDefinition(const UEquipmentAbilityNodeDefinition* CurrentDefinition, TSet<const UEquipmentAbilityNodeDefinition*>& Visited)
{
	if (CurrentDefinition == nullptr)
	{
		return nullptr;
	}

	if (Visited.Contains(CurrentDefinition))
	{
		UE_LOG(LogMyVamSur, Warning, TEXT("Definition is already visited: %s"), *CurrentDefinition->GetName());
		return nullptr;
	}

	UAbilityTreeNode* CurrentNode = NewObject<UAbilityTreeNode>(this);
	if (!CurrentNode)
	{
		UE_LOG(LogMyVamSur, Warning, TEXT("Failed to create new node from definition %s"), *CurrentDefinition->GetName());
		return nullptr;
	}

	CurrentNode->SetOwingEquipment(GetOwner<AEquipment>());
	CurrentNode->SetNodeDefinition(CurrentDefinition);
	Visited.Add(CurrentDefinition);

	for (const UEquipmentAbilityNodeDefinition* ChildNodeDefinition : CurrentDefinition->GetChildren())
	{
		if (UAbilityTreeNode* ChildNode = CreateTreeFromDefinition(ChildNodeDefinition, Visited))
		{
			CurrentNode->AddChildNode(ChildNode);
		}
	}

	return CurrentNode;
}
