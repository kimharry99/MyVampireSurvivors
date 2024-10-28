// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipments/EquipmentItem.h"

// Sets default values
AEquipmentItem::AEquipmentItem()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEquipmentItem::BeginPlay()
{
	Super::BeginPlay();
}

bool AEquipmentItem::IsUsable() const
{
	return true;
}

void AEquipmentItem::UseEquipment()
{
	check(IsUsable());
}

