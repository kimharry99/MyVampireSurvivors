// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipments/ActiveEquipmentItem.h"

#include "MyVamSurLogChannels.h"

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

void AActiveEquipmentItem::SetEquipmentStat(int Level)
{
	if (const FActiveEquipmentStat* EquipmentStat = EquipmentStatTable->FindRow<FActiveEquipmentStat>(*FString::FromInt(Level), TEXT("")))
	{
		SetCoolDown(EquipmentStat->CoolDown);
	}
	else
	{
		UE_LOG(LogMyVamSur, Warning, TEXT("Failed to find the equipment stat."));
	}
}

float AActiveEquipmentItem::GetCoolDown() const
{
	return CoolDown;
}

void AActiveEquipmentItem::SetCoolDown(float NewCoolDown)
{
	CoolDown = NewCoolDown;
	RemainCoolDown = FMathf::Min(RemainCoolDown, CoolDown);
}
