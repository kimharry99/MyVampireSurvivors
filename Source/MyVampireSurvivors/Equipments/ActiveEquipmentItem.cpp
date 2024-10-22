// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipments/ActiveEquipmentItem.h"

AActiveEquipmentItem::AActiveEquipmentItem()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AActiveEquipmentItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (RemainCoolDown > 0.0f)
	{
		RemainCoolDown -= DeltaTime;
	}
}

bool AActiveEquipmentItem::IsUsable() const
{
	bool bIsUsable = Super::IsUsable();

	bIsUsable &= RemainCoolDown <= 0.0f;
	return bIsUsable;
}

void AActiveEquipmentItem::UseEquipment()
{
	Super::UseEquipment();

	if (RemainCoolDown <= 0.0f)
	{
		RemainCoolDown = CoolDown;
	}
}

float AActiveEquipmentItem::GetCoolDown() const
{
	return CoolDown;
}
