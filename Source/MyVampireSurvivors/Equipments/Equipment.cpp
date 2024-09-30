// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipments/Equipment.h"

// Sets default values
AEquipment::AEquipment()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEquipment::BeginPlay()
{
	Super::BeginPlay();
}

bool AEquipment::IsUsable() const
{
	return true;
}

void AEquipment::UseEquipment()
{
	check(IsUsable());
}

