// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipments/SpreadProjectileLauncher.h"

void ASpreadProjectileLauncher::CalculateFireLocationAndRotation(OUT TArray<FVector>& OutFireLocations, OUT TArray<FRotator>& OutFireRotations)
{
	const float FirePositionDistance = 50.0f;
	const float AngleStep = AngleRange / (ProjectileCount - 1);
	const float MinAngle = -AngleRange * 0.5f;

	for (int i = 0; i < ProjectileCount; ++i)
	{
		const FRotator SpawnRotation = GetActorRotation() + FRotator(0.0f, MinAngle + i * AngleStep, 0.0f);
		const FVector SpawnLocation = GetActorLocation() + SpawnRotation.Vector() * FirePositionDistance;
		OutFireLocations.Add(SpawnLocation);
		OutFireRotations.Add(SpawnRotation);
	}
}
