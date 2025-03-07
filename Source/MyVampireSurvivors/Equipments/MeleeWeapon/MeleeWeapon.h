// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Equipments/EquipmentCore/AnimatedEquipment.h"
#include "MeleeWeapon.generated.h"


UCLASS()
class MYVAMPIRESURVIVORS_API AMeleeWeapon : public AAnimatedEquipment
{
	GENERATED_BODY()

public:
	AMeleeWeapon(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
