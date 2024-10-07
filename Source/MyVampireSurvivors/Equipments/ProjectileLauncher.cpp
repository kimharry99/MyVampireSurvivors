// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipments/ProjectileLauncher.h"

void AProjectileLauncher::UseEquipment()
{
	Super::UseEquipment();

	TArray<FVector> FireLocations;
	TArray<FRotator> FireRotations;
	CalculateFireLocationAndRotation(FireLocations, FireRotations);
	Fire(FireLocations, FireRotations);
}

void AProjectileLauncher::CalculateFireLocationAndRotation(OUT TArray<FVector>& OutFireLocations, OUT TArray<FRotator>& OutFireRotations)
{

}

void AProjectileLauncher::Fire(const TArray<FVector>& FireLocations, const TArray<FRotator>& FireRotations)
{
	check(FireLocations.Num() == FireRotations.Num());
	const int ProjectileCount = FireLocations.Num();
	for (int i = 0; i < ProjectileCount; ++i)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = this;
		SpawnInfo.Instigator = GetInstigator();

		AProjectileWeapon* Projectile = GetWorld()->SpawnActor<AProjectileWeapon>(ProjectileClass, FireLocations[i], FireRotations[i], SpawnInfo);
	}
}
