// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Equipments/EquipmentCore/Equipment.h"
#include "ProjectileLauncher.generated.h"

/**
 * ProjectileLauncher
 *
 * Projectile launcher is a equipment that can launch a projectile.
 */
UCLASS(Blueprintable, Abstract)
class MYVAMPIRESURVIVORS_API AProjectileLauncher : public AEquipment
{
	GENERATED_BODY()

public:
	AProjectileLauncher(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
