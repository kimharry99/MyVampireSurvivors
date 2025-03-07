// Fill out your copyright notice in the Description page of Project Settings.


#include "LauncherAbilityTreeComponent.h"

#include "LauncherAbilityNodeDefinition.h"
#include "Equipments/EquipmentCore/AbilityTreeNode.h"
#include "Equipments/EquipmentCore/StatComponent.h"
#include "IProjectileLauncherStats.h"
#include "ProjectileSpawnStrategy.h"
#include "MyVamSurLogChannels.h"


//////////////////////////////////////////////////////////////////////
// ULauncherAbilityTreeComponent
ULauncherAbilityTreeComponent::ULauncherAbilityTreeComponent()
	: Super()
{
}

void ULauncherAbilityTreeComponent::UpdateStat(UStatComponent* StatComponent) const
{
	if (StatComponent)
	{
		StatComponent->Reset();
	}
	else
	{
		UE_CLOG(GetOwner(), LogMyVamSur, Warning, TEXT("Input StatComponent is NULL at equipment %s, component %s"), *(GetOwner()->GetName()), *GetName());
	}

	FLauncherStatusUpgradingVisitor Visitor(StatComponent);
	TraverseTree(Visitor);
}

//////////////////////////////////////////////////////////////////////
// FLauncherStatusUpgradingVisitor
ULauncherAbilityTreeComponent::FLauncherStatusUpgradingVisitor::FLauncherStatusUpgradingVisitor(UStatComponent* InTargetStatComponent)
	: TargetStatComponent(InTargetStatComponent)
{
}

void ULauncherAbilityTreeComponent::FLauncherStatusUpgradingVisitor::Process(UAbilityTreeNode* Node)
{
	if (!Node || !TargetStatComponent.IsValid())
	{
		return;
	}

	if (const ULauncherAbilityNodeDefinition* NodeDefinition = Node->GetNodeDefinition<ULauncherAbilityNodeDefinition>())
	{
		if (IProjectileLauncherStats* LauncherStats = Cast<IProjectileLauncherStats>(TargetStatComponent))
		{
			LauncherStats->AddProjectileCount(NodeDefinition->ProjectileCount);
			LauncherStats->AddProjectileSpeed(NodeDefinition->ProjectileSpeed);
			LauncherStats->AddAttackSpeed(NodeDefinition->AttackSpeed);
			LauncherStats->AddAttackSpeedMultiplier(NodeDefinition->AttackSpeedMultiplier);

			for (const FLauncherStatOverwriteData& OverwriteData : NodeDefinition->OverwriteDataArray)
			{
				switch (OverwriteData.StatType)
				{
					case ELauncherOverwrittenStatType::Projectile:
					{
						LauncherStats->SetProjectileWeaponClass(OverwriteData.ProjectileWeaponClass);
						break;
					}
					case ELauncherOverwrittenStatType::SpawnStrategy:
					{
						UProjectileSpawnStrategy* NewStrategy = NewObject<UProjectileSpawnStrategy>(TargetStatComponent.Get(), OverwriteData.SpawnStrategyClass);
						LauncherStats->SetSpawnStrategy(NewStrategy);
						break;
					}
					default:
					{
						UE_LOG(LogMyVamSur, Warning, TEXT("Wrong overwritten stat type %s"), *(NodeDefinition->GetName()));
						break;
					}
				}
			}
		}
	}
}

bool ULauncherAbilityTreeComponent::FLauncherStatusUpgradingVisitor::IsVisitable(UAbilityTreeNode* Node)
{
	return Node ? Node->IsActive() : false;
}
