// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipments/ActiveEquipment.h"
#include "Weapons/ProjectileWeapon.h"
#include "ProjectileLauncher.generated.h"

/**
 * ProjectileLauncher
 * 
 * Projectile launcher is a equipment that can launch a projectile.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API AProjectileLauncher : public AActiveEquipment
{
	GENERATED_BODY()

public:
	//~AActiveEquipment interface
	virtual void UseEquipment() override;
	//~End of AActiveEquipment interface

private:
	UPROPERTY(EditDefaultsOnly, Category = "Equipment|Launcher", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectileWeapon> ProjectileClass;

	/**
	 * Fire the projectile.
	 */
	void Fire();
};
