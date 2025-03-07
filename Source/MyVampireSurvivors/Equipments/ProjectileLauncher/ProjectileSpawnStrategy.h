// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ProjectileSpawnStrategy.generated.h"

UCLASS(Abstract)
class MYVAMPIRESURVIVORS_API UProjectileSpawnStrategy : public UObject
{
	GENERATED_BODY()

public:
	virtual TArray<FTransform> GetSpawnTransform(const FTransform& Origin, const int Count) const;
};
