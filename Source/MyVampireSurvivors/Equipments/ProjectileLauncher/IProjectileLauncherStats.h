// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "ProjectileWeapon.h"
#include "IProjectileLauncherStats.generated.h"

class AProjectileWeapon;
class UProjectileSpawnStrategy;

UINTERFACE(MinimalAPI)
class UProjectileLauncherStats : public UInterface
{
	GENERATED_BODY()
};

class MYVAMPIRESURVIVORS_API IProjectileLauncherStats
{
	GENERATED_BODY()

public:
	virtual float GetCooldown() const = 0;
	virtual void AddAttackSpeed(float Value) = 0;
	virtual void AddAttackSpeedMultiplier(float Value) = 0;

	virtual int GetProjectileCount() const = 0;
	virtual void AddProjectileCount(int Value) = 0;

	virtual float GetProjectileSpeed() const = 0;
	virtual void AddProjectileSpeed(float Value) = 0;

	virtual TSubclassOf<AProjectileWeapon> GetProjectileWeaponClass() const = 0;
	virtual void SetProjectileWeaponClass(TSubclassOf<AProjectileWeapon> NewProjectileWeaponClass) = 0;

	virtual UProjectileSpawnStrategy* GetSpawnStrategy() const = 0;
	virtual void SetSpawnStrategy(UProjectileSpawnStrategy* NewSpawnStrategy) = 0;
};
