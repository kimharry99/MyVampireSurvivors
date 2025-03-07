// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProjectileSpawnStrategy.h"
#include "SpreadProjectileSpawnStrategy.generated.h"

UCLASS()
class MYVAMPIRESURVIVORS_API USpreadProjectileSpawnStrategy : public UProjectileSpawnStrategy
{
	GENERATED_BODY()

private:
	float AngleRange = 20.0f;
	float FirePositionDistance = 50.0f;

public:
	void Initialize(const int NewAngleRange, const int NewFirePositionDistance);

public:
	//~UProjectileSpawnStrategy interface
	virtual TArray<FTransform> GetSpawnTransform(const FTransform& Origin, const int Count) const override;
	//~End of UProjectileSpawnStrategy interface
};
