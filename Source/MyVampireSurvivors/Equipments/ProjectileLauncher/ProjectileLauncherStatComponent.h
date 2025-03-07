// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Equipments/EquipmentCore/StatComponent.h"
#include "IProjectileLauncherStats.h"
#include "ProjectileLauncherStatComponent.generated.h"

class AProjectileWeapon;
class UProjectileSpawnStrategy;

/**
 *
 */
UCLASS(ClassGroup = Equipment)
class MYVAMPIRESURVIVORS_API UProjectileLauncherStatComponent : public UStatComponent, public IProjectileLauncherStats
{
	GENERATED_BODY()

public:
	//~IProjectileLauncherStats interface
	virtual int GetProjectileCount() const override;
	virtual void AddProjectileCount(int Value) override;
	virtual float GetProjectileSpeed() const override;
	virtual void AddProjectileSpeed(float Value) override;

	virtual float GetCooldown() const override;
	virtual void AddAttackSpeed(float Value) override;
	virtual void AddAttackSpeedMultiplier(float Value) override;

	virtual TSubclassOf<AProjectileWeapon> GetProjectileWeaponClass() const override;
	virtual void SetProjectileWeaponClass(TSubclassOf<AProjectileWeapon> NewProjectileWeaponClass) override;
	virtual UProjectileSpawnStrategy* GetSpawnStrategy() const override;
	virtual void SetSpawnStrategy(UProjectileSpawnStrategy* NewSpawnStrategy) override;
	//~End of IProjectileLauncherStats interface

	//~UStatComponent interface
	virtual void Reset() override;
	//~End of UStatComponent interface

private:
	UPROPERTY(Category = Equipment, VisibleAnywhere, Transient)
	float AttackSpeed = 0.0f;
	UPROPERTY(Category = Equipment, VisibleAnywhere, Transient)
	float AttackSpeedMultiplier = 0.0f;

	UPROPERTY(Category = Equipment, VisibleAnywhere, Transient)
	int ProjectileCount = 0;
	UPROPERTY(Category = Equipment, VisibleAnywhere, Transient)
	float ProjectileSpeed = 0.0f;

	UPROPERTY(Category = Equipment, VisibleAnywhere, Transient)
	TSubclassOf<AProjectileWeapon> ProjectileWeaponClass;

	UPROPERTY()
	TObjectPtr<UProjectileSpawnStrategy> SpawnStrategy;
};
