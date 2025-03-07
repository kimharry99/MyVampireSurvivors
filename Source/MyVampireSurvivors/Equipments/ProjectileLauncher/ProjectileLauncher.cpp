// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileLauncher.h"

#include "Equipments/EquipmentCore/EquipmentStateMachine.h"
#include "LauncherAbilityTreeComponent.h"
#include "ProjectileLauncherStatComponent.h"
#include "ProjectileLauncherUsageComponent.h"
#include "MyVamSurLogChannels.h"


//////////////////////////////////////////////////////////////////////
// AProjectileLauncher
AProjectileLauncher::AProjectileLauncher(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer
				.SetDefaultSubobjectClass<UProjectileLauncherStatComponent>(AEquipment::StatComponentName)
				.SetDefaultSubobjectClass<ULauncherAbilityTreeComponent>(AEquipment::UpgradeComponentName)
				.SetDefaultSubobjectClass<UProjectileLauncherUsageComponent>(AEquipment::UsageComponentName))
{
	UProjectileLauncherUsageComponent* LauncherUsageComp = CastChecked<UProjectileLauncherUsageComponent>(GetUsageComponent());
	UEquipmentStateMachine* EquipmentStateMachine = GetStateMachine();
	check(EquipmentStateMachine);

	LauncherUsageComp->OnCooldownEnded.Add(FSimpleMulticastDelegate::FDelegate::CreateUObject(EquipmentStateMachine, &UEquipmentStateMachine::TransitionCooldownToReady));
}
