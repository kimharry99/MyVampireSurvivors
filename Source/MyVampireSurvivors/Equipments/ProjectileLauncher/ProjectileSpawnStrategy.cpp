// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileSpawnStrategy.h"

TArray<FTransform> UProjectileSpawnStrategy::GetSpawnTransform(const FTransform& Origin, const int Count) const
{
	// Empty implementation
	UE_LOG(LogTemp, Fatal, TEXT("%s: GetSpawnTransform() should not be called!"), *GetNameSafe(this));
	check(false);

	return TArray<FTransform>();
}
