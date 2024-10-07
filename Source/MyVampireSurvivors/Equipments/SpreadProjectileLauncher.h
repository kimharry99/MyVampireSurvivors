// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipments/ProjectileLauncher.h"
#include "SpreadProjectileLauncher.generated.h"

/**
 * The projectile launcher fires multiple projectiles with a spread angle.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API ASpreadProjectileLauncher : public AProjectileLauncher
{
	GENERATED_BODY()

protected:
	//~AProjectileLauncher interface
	virtual void CalculateFireLocationAndRotation(OUT TArray<FVector>& OutFireLocations, OUT TArray<FRotator>& OutFireRotations) override;
	//~End of AProjectileLauncher interface

private:
	/** Number of projectiles fired per shot. */
	UPROPERTY(EditDefaultsOnly, Category = "Equipment|Launcher", meta = (AllowPrivateAccess = "true"))
	int ProjectileCount = 0;

	/** Angle range of the spread. */
	UPROPERTY(EditDefaultsOnly, Category = "Equipment|Launcher", meta = (AllowPrivateAccess = "true"))
	float AngleRange = 0.0f;
};
