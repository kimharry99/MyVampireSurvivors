// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeWeaponAbilityTreeComponent.h"

#include "IMeleeWeaponStats.h"
#include "Equipments/EquipmentCore/IEquipmentAnimationStats.h"
#include "MeleeWeaponAbilityNodeDefinition.h"
#include "MyVamSurLogChannels.h"
#include "Equipments/EquipmentCore/StatComponent.h"
#include "Equipments/EquipmentCore/AbilityTreeNode.h"

UMeleeWeaponAbilityTreeComponent::UMeleeWeaponAbilityTreeComponent()
	: Super()
{
}

void UMeleeWeaponAbilityTreeComponent::UpdateStat(UStatComponent* StatComponent) const
{
	if (StatComponent)
	{
		StatComponent->Reset();
	}

	FMeleeWeaponStatusUpgradingVisitor Visitor(StatComponent);
	TraverseTree(Visitor);
}


//////////////////////////////////////////////////////////////////////
// FMeleeWeaponStatusUpgradingVisitor
UMeleeWeaponAbilityTreeComponent::FMeleeWeaponStatusUpgradingVisitor::FMeleeWeaponStatusUpgradingVisitor(UStatComponent* InTargetStatComponent)
	: TargetStatComponent(InTargetStatComponent)
{
}

void UMeleeWeaponAbilityTreeComponent::FMeleeWeaponStatusUpgradingVisitor::Process(UAbilityTreeNode* Node)
{
	if (!Node || !TargetStatComponent.IsValid())
	{
		return;
	}

	if (const UMeleeWeaponAbilityNodeDefinition* NodeDefinition = Node->GetNodeDefinition<UMeleeWeaponAbilityNodeDefinition>())
	{
		if (IMeleeWeaponStats* MeleeWeaponStats = Cast<IMeleeWeaponStats>(TargetStatComponent))
		{
			MeleeWeaponStats->AddDamage(NodeDefinition->Damage);
			MeleeWeaponStats->AddDamageMultiplier(NodeDefinition->DamageMultiplier);

			MeleeWeaponStats->AddAttackSpeed(NodeDefinition->AttackSpeed);
			MeleeWeaponStats->AddAttackSpeedMultiplier(NodeDefinition->AttackSpeedMultiplier);

			MeleeWeaponStats->AddAttackRangeMultiplier(NodeDefinition->HitboxMultiplier);
		}

		if (IEquipmentAnimationStats* AnimationStats = Cast<IEquipmentAnimationStats>(TargetStatComponent))
		{
			for (const FMeleeWeaponStatOverwriteData& OverwriteData : NodeDefinition->OverwriteDataArray)
			{
				switch (OverwriteData.StatType)
				{
				case EMeleeWeaponOverwrittenStatType::AnimationData:
					AnimationStats->SetAnimationData(OverwriteData.NewAnimationData);
					break;
				case EMeleeWeaponOverwrittenStatType::None:
					UE_LOG(LogMyVamSur, Warning, TEXT("Wrong overwritten stat type %s"), *(NodeDefinition->GetName()));
					break;
				}
			}
		}
	}
}

bool UMeleeWeaponAbilityTreeComponent::FMeleeWeaponStatusUpgradingVisitor::IsVisitable(UAbilityTreeNode* Node)
{
	return Node ? Node->IsActive() : false;
}
