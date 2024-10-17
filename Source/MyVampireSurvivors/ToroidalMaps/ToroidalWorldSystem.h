// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyVamSurGameMode.h"
#include "ToroidalWorldSystem.generated.h"

class AToroidalMap;

namespace FToroidalWorldSystem
{
	/**
	 * Get the current toroidal world system.
	 */
	template<typename T>
	FORCEINLINE T* GetCurrent(UWorld* World)
	{
		if (World)
		{
			return Cast<T>(World->GetAuthGameMode<AMyVamSurGameMode>()->GetToroidalWorldSystem());
		}
		return (T*)nullptr;
	}
}

/**
 * Utility class to manage the toroidal world system.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UToroidalWorldSystem : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * Initialize the toroidal world system.
	 * @param ToroidalMap The toroidal map to use.
	 */
	void Initialize(AToroidalMap* LevelToroidalMap);

private:
	UPROPERTY()
	TObjectPtr<AToroidalMap> ToroidalMap;

public:
	/**
	 * Wrap a position in toroidal topology.
	 */
	FVector WrapPosition3D(const FVector& Position) const;

	/**
	 * Returns true, if the point is inside the box on toroidal topology.
	 */
	bool IsInsideBoxOnTorus(const FVector& Point, const FBox& Box) const;

	/**
	 * Calculate displacement to the closest point corresponding to the destination on a toroidal map.
	 */
	FVector CalculateDisplacement(const FVector& From, const FVector& To) const;

private:
	double WrapValue(double Value, double RangeMin, double RangeSize) const;

	/**
	 * Calculate the distance between two points on toroidal topology.
	 */
	double CalculateDistance1D(double From, double To, double RangeSize) const;

	double CalculateSignedDistance1D(double From, double To, double RangeSize) const;
};
