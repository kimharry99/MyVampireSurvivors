// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeWeapon.h"

#include "Equipments/EquipmentCore/EquipmentStateMachine.h"
#include "MeleeWeaponStatComponent.h"
#include "MeleeWeaponAbilityTreeComponent.h"
#include "MeleeWeaponUsageComponent.h"

//////////////////////////////////////////////////////////////////////
// AMeleeWeapon
AMeleeWeapon::AMeleeWeapon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer
				.SetDefaultSubobjectClass<UMeleeWeaponStatComponent>(AEquipment::StatComponentName)
				.SetDefaultSubobjectClass<UMeleeWeaponAbilityTreeComponent>(AEquipment::UpgradeComponentName)
				.SetDefaultSubobjectClass<UMeleeWeaponUsageComponent>(AEquipment::UsageComponentName))
{
	UMeleeWeaponUsageComponent* MeleeWeaponUsageComp = CastChecked<UMeleeWeaponUsageComponent>(GetUsageComponent());
	UEquipmentStateMachine* EquipmentStateMachine = GetStateMachine();
	check(EquipmentStateMachine);

	MeleeWeaponUsageComp->OnCooldownEnded.Add(FSimpleMulticastDelegate::FDelegate::CreateUObject(EquipmentStateMachine, &UEquipmentStateMachine::TransitionCooldownToReady));
}
