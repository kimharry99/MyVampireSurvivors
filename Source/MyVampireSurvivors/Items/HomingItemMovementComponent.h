// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "HomingItemMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UHomingItemMovementComponent : public UProjectileMovementComponent
{
	GENERATED_BODY()

public:
	UHomingItemMovementComponent();

protected:
	//~UProjectileMovementComponent interface
	virtual FVector ComputeHomingAcceleration(const FVector& InVelocity, float DeltaTime) const;
	//~End of UProjectileMovementComponent interface
};
