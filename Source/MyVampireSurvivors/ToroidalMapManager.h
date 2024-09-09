// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "ToroidalMap.h"

/**
 * 
 */
class MYVAMPIRESURVIVORS_API ToroidalMapManager
{

public:
	static ToroidalMapManager* GetInstance();
	void Initialize(AToroidalMap* NewMap);

	/**
	 * Call the HandleMapBoundary function of the map if it exists
	 * 
	 * @param PlayerCharacter - The player character of game
	 */
	void HandleMapBoundary(APlayerCharacter* PlayerCharacter) const;

	/**
	 * Get the map range from the toroidal map.
	 * 
	 * @return The map range of the toroidal map
	 */
	const FBox GetMapRange() const;

private:
	ToroidalMapManager() = default;

	AToroidalMap* Map;
};
