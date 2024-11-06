// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipments/EquipmentItem.h"

#include "MyVamSurLogChannels.h"

//////////////////////////////////////////////////////////////////////
// FEquipmentStat
const FName FEquipmentStat::MaxLevelRowName(TEXT("MAX"));

//////////////////////////////////////////////////////////////////////
// AEquipmentItem

// Sets default values
AEquipmentItem::AEquipmentItem()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEquipmentItem::BeginPlay()
{
	Super::BeginPlay();

	InitializeLevel();
}

bool AEquipmentItem::IsUsable() const
{
	return true;
}

void AEquipmentItem::UseEquipment()
{
	check(IsUsable());
}

int AEquipmentItem::GetEquipmentLevel() const
{
	return EquipmentLevel;
}

bool AEquipmentItem::CanUpgrade() const
{
	if (EquipmentStatTable == nullptr)
	{
		return false;
	}
	
	if (EquipmentLevel >= MaxEquipmentLevel)
	{
		return false;
	}

	return true;
}

void AEquipmentItem::Upgrade()
{
	if (CanUpgrade())
	{
		SetEquipmentStat(++EquipmentLevel);
	}
}

void AEquipmentItem::SetEquipmentStat(int Level)
{
	// Empty implementation
}

void AEquipmentItem::InitializeLevel()
{
	EquipmentLevel = 1;
	SetEquipmentStat(EquipmentLevel);

	check(EquipmentStatTable);
	if (FEquipmentStat* MaxEquipmentStat = EquipmentStatTable->FindRow<FEquipmentStat>(FEquipmentStat::MaxLevelRowName, TEXT("")))
	{
		MaxEquipmentLevel = MaxEquipmentStat->Level;
	}
	else
	{
		UE_LOG(LogMyVamSur, Warning, TEXT("Failed to find the max equipment stat."));
	}
}
