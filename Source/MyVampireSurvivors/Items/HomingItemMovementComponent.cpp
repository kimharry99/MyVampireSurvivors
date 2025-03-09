// Fill out your copyright notice in the Description page of Project Settings.


#include "HomingItemMovementComponent.h"

#include "ToroidalMaps/ToroidalWorldSystem.h"

UHomingItemMovementComponent::UHomingItemMovementComponent()
{
	bIsHomingProjectile = true;
	bShouldBounce = false;
	ProjectileGravityScale = 0.0f;
	bRotationFollowsVelocity = false;
	InitialSpeed = 0.0f;
}

FVector UHomingItemMovementComponent::ComputeHomingAcceleration(const FVector& InVelocity, float DeltaTime) const
{
	UToroidalWorldSystem* ToroidalWorldSystem = FToroidalWorldSystem::GetCurrent<UToroidalWorldSystem>(GetWorld());
	if (ToroidalWorldSystem)
	{
		const FVector StartLocation = UpdatedComponent->GetComponentLocation();
		const FVector TargetLocation = HomingTargetComponent->GetComponentLocation();
		FVector HomingAcceleration = ToroidalWorldSystem->ComputeToroidalDisplacement(StartLocation, TargetLocation).GetSafeNormal() * HomingAccelerationMagnitude;
		return HomingAcceleration;
	}

	return Super::ComputeHomingAcceleration(InVelocity, DeltaTime);
}
