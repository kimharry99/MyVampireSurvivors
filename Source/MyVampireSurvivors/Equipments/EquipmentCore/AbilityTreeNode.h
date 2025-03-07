// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UpgradeOption.h"
#include "AbilityTreeNode.generated.h"

class AEquipment;
class UEquipmentAbilityNodeDefinition;

UCLASS(ClassGroup = Equipment)
class MYVAMPIRESURVIVORS_API UAbilityTreeNode : public UUpgradeOption
{
	GENERATED_BODY()

public:
	//~IDisplableObject interface
	virtual const FText GetObjectName() const override;
	virtual const FText GetDescription() const override;
	virtual const UPaperSprite* GetIcon() const override;
	//~End of IDisplableObject interface
	
	//~UUgradeOption interface
	virtual bool IsActive() const override;
	virtual AEquipment* GetOwningEquipment() const override;
	//~End of UUgradeOption interface

	void Activate();
	void SetOwingEquipment(AEquipment* NewOwingEquipment);
	
	template <typename T>
	const T* GetNodeDefinition() const
	{
		return Cast<const T>(NodeDefinition);
	}

	void SetNodeDefinition(const UEquipmentAbilityNodeDefinition* NewNodeDefinition);

private:
	bool bIsActive = false;

	UPROPERTY()
	TObjectPtr<const UEquipmentAbilityNodeDefinition> NodeDefinition;

	TWeakObjectPtr<AEquipment> OwingEquipment = nullptr;

public:
	TArray<const UAbilityTreeNode*> GetChildren() const;
	TArray<UAbilityTreeNode*> GetChildren();

	void AddChildNode(UAbilityTreeNode* ChildNode);

private:
	UPROPERTY()
	TArray<UAbilityTreeNode*> ChildNodes;
};
