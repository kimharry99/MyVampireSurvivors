// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipments/ProjectileLauncher.h"

void AProjectileLauncher::UseEquipment()
{
	Super::UseEquipment();

	Fire();
}

void AProjectileLauncher::Fire()
{
	const int ProjectileCount = 1;
	for (int i = 0; i < ProjectileCount; ++i)
	{
		FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 50.0f;
		FRotator SpawnRotation = FRotator::ZeroRotator;
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = this;
		SpawnInfo.Instigator = GetInstigator();

		AProjectileWeapon* Projectile = GetWorld()->SpawnActor<AProjectileWeapon>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnInfo);
	}
}
