// Fill out your copyright notice in the Description page of Project Settings.


#include "SpreadProjectileSpawnStrategy.h"

void USpreadProjectileSpawnStrategy::Initialize(const int NewAngleRange, const int NewFirePositionDistance)
{
	AngleRange = NewAngleRange;
	FirePositionDistance = NewFirePositionDistance;
}

TArray<FTransform> USpreadProjectileSpawnStrategy::GetSpawnTransform(const FTransform& Origin, const int Count) const
{
	TArray<FTransform> OutSpawnTransforms;

	const float AngleStep = Count > 1 ? AngleRange / (Count - 1) : 0.0f;
	const float MinAngle = Count > 1 ? -AngleRange * 0.5f : 0.0f;

	for (int i = 0; i < Count; ++i)
	{
		const FRotator SpawnRotation = Origin.GetRotation().Rotator() + FRotator(0.0f, MinAngle + i * AngleStep, 0.0f);
		const FVector SpawnLocation = Origin.GetLocation() + SpawnRotation.Vector() * FirePositionDistance;

		OutSpawnTransforms.Add(FTransform(SpawnRotation, SpawnLocation, FVector(1.0f)));
	}

	return OutSpawnTransforms;
}
