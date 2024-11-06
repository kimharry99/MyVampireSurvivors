// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipments/ProjectileLauncher.h"
#include "SpreadProjectileLauncher.generated.h"


USTRUCT(BlueprintType)
struct MYVAMPIRESURVIVORS_API FSpreadLauncherStat : public FActiveEquipmentStat
{
	GENERATED_BODY()

	FSpreadLauncherStat()
	: ProjectileCount(1)
	, AngleRange(20.0f)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	int ProjectileCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	float AngleRange;
};


/**
 * The projectile launcher fires multiple projectiles with a spread angle.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API ASpreadProjectileLauncher : public AProjectileLauncher
{
	GENERATED_BODY()

public:
	ASpreadProjectileLauncher();

protected:
	//~AEquipmentItem interface
	virtual void SetEquipmentStat(int Level) override;
	//~End of AEquipmentItem interface
	
	//~AProjectileLauncher interface
	virtual void CalculateFireLocationAndRotation(OUT TArray<FVector>& OutFireLocations, OUT TArray<FRotator>& OutFireRotations) override;
	//~End of AProjectileLauncher interface

private:
	/** Number of projectiles fired per shot. */
	UPROPERTY(Transient, VisibleAnywhere, Category = "Equipment|Launcher")
	int ProjectileCount = 0;

	/** Angle range of the spread. */
	UPROPERTY(Transient, VisibleAnywhere, Category = "Equipment|Launcher")
	float AngleRange = 0.0f;
};
