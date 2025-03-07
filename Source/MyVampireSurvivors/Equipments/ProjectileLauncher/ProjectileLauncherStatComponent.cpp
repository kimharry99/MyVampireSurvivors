// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileLauncherStatComponent.h"

#include "ProjectileWeapon.h"
#include "SpreadProjectileSpawnStrategy.h"
#include "MyVamSurLogChannels.h"

int UProjectileLauncherStatComponent::GetProjectileCount() const
{
	return ProjectileCount;
}

void UProjectileLauncherStatComponent::AddProjectileCount(int Value)
{
	ProjectileCount += Value;
}

float UProjectileLauncherStatComponent::GetProjectileSpeed() const
{
	return ProjectileSpeed;
}

void UProjectileLauncherStatComponent::AddProjectileSpeed(float Value)
{
	ProjectileSpeed += Value;
}

float UProjectileLauncherStatComponent::GetCooldown() const
{
	float TotalAttackSpeed = AttackSpeed * AttackSpeedMultiplier;
	if (TotalAttackSpeed > 0.0f)
	{
		return 1.0f / TotalAttackSpeed;
	}

	UE_CLOG(GetOwner(), LogMyVamSur, Warning, TEXT("Attack speed is zero %s"), *(GetOwner()->GetName()));
	return 1.0f;
}

void UProjectileLauncherStatComponent::AddAttackSpeed(float Value)
{
	AttackSpeed += Value;
}

void UProjectileLauncherStatComponent::AddAttackSpeedMultiplier(float Value)
{
	AttackSpeedMultiplier += Value;
}

TSubclassOf<AProjectileWeapon> UProjectileLauncherStatComponent::GetProjectileWeaponClass() const
{
	return ProjectileWeaponClass;
}

void UProjectileLauncherStatComponent::SetProjectileWeaponClass(TSubclassOf<AProjectileWeapon> NewProjectileWeaponClass)
{
	if (ProjectileWeaponClass == NewProjectileWeaponClass)
	{
		return;
	}

	ProjectileWeaponClass = NewProjectileWeaponClass;
}

UProjectileSpawnStrategy* UProjectileLauncherStatComponent::GetSpawnStrategy() const
{
	return SpawnStrategy;
}

void UProjectileLauncherStatComponent::SetSpawnStrategy(UProjectileSpawnStrategy* NewSpawnStrategy)
{
	if (SpawnStrategy == NewSpawnStrategy)
	{
		return;
	}

	SpawnStrategy = NewSpawnStrategy;
}

void UProjectileLauncherStatComponent::Reset()
{
	AttackSpeed = 0.0f;
	AttackSpeedMultiplier = 0.0f;

	ProjectileCount = 0;
	ProjectileSpeed = 0.0f;

	ProjectileWeaponClass = nullptr;

	SpawnStrategy = nullptr;
}
