// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipments/ActiveEquipment.h"

AActiveEquipment::AActiveEquipment()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AActiveEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (RemainCoolDown > 0.0f)
	{
		RemainCoolDown -= DeltaTime;
	}
}

bool AActiveEquipment::IsUsable() const
{
	bool bIsUsable = Super::IsUsable();

	bIsUsable &= RemainCoolDown <= 0.0f;
	return bIsUsable;
}

void AActiveEquipment::UseEquipment()
{
	Super::UseEquipment();

	if (RemainCoolDown <= 0.0f)
	{
		RemainCoolDown = CoolDown;
	}
}

float AActiveEquipment::GetCoolDown() const
{
	return CoolDown;
}
