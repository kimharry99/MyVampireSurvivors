// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipments/ActiveEquipmentItem.h"
#include "Weapons/ProjectileWeapon.h"
#include "ProjectileLauncher.generated.h"

/**
 * ProjectileLauncher
 * 
 * Projectile launcher is a equipment that can launch a projectile.
 */
UCLASS(Abstract)
class MYVAMPIRESURVIVORS_API AProjectileLauncher : public AActiveEquipmentItem
{
	GENERATED_BODY()

public:
	//~AActiveEquipment interface
	virtual void UseEquipment() override;
	//~End of AActiveEquipment interface

protected:
	/**
	 * Calculate the fire location and rotation for spawning the projectiles.
	 */
	virtual void CalculateFireLocationAndRotation(OUT TArray<FVector>& OutFireLocations, OUT TArray<FRotator>& OutFireRotations);

	/**
	 * Fire the projectile.
	 * Spawn the projectiles at the given fire locations and rotations.
	 */
	virtual void Fire(const TArray<FVector>& FireLocations, const TArray<FRotator>& FireRotations);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Equipment|Launcher", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectileWeapon> ProjectileClass;
};
