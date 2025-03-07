// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentAutoActivator.h"

#include "Equipments/EquipmentCore/Equipment.h"

UEquipmentAutoActivator::UEquipmentAutoActivator(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UEquipmentAutoActivator::RegisterAndUseEquipment(AEquipment* Equipment) const
{
	if (Equipment)
	{
		Equipment->OnEquipmentUsable.Add(FOnEquipmentUsable::FDelegate::CreateUObject(this, &ThisClass::ExecuteUse));
		Equipment->Use();
	}
}

void UEquipmentAutoActivator::ExecuteUse(TWeakObjectPtr<AEquipment> Equipment) const
{
	if (Equipment.IsValid())
	{
		Equipment->Use();
	}
}
