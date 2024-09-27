// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/ActiveWeapon.h"

void AActiveWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (RemainCoolDown > 0.0f)
	{
		RemainCoolDown -= DeltaTime;
	}
}

bool AActiveWeapon::IsUsable() const
{
	bool bIsUsable = Super::IsUsable();
	
	bIsUsable &= RemainCoolDown <= 0.0f;
	return bIsUsable;
}

void AActiveWeapon::UseWeapon()
{
	Super::UseWeapon();

	if (RemainCoolDown <= 0.0f)
	{
		RemainCoolDown = CoolDown;
	}
}
