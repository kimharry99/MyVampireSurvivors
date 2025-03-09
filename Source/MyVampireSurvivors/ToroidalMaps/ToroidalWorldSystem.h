// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModes/MyVamSurGameMode.h"
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
	
	TArray<FBox2D> GetDistortionZones() const;
	void SetDistortionZone(const FBox& WorldDistortionZone);

	/**
	 * Calculate displacement to the closest point corresponding to the destination on a toroidal map.
	 */
	FVector CalculateDisplacement(const FVector& From, const FVector& To) const;

	/** Refine location defined in world space */
	FVector RefineLocation(const FVector& Location, const bool bActiveDistortion = true) const;

private:
	UPROPERTY()
	TObjectPtr<AToroidalMap> ToroidalMap;

	FVector TransformToTorus(const FVector& Location) const;
	FVector2D TransformToTorus(const FVector2D& Location) const;

	FVector TransformToWorld(const FVector& Location, const bool bActiveDistortion) const;

	TArray<TPair<FIntVector2, FBox2D>> DistortionZones;
};
