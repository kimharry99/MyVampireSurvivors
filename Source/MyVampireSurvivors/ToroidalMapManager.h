// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToroidalMap.h"

/**
 * 
 */
class MYVAMPIRESURVIVORS_API ToroidalMapManager
{

public:
	static ToroidalMapManager* GetInstance();
	void Initialize(AToroidalMap* NewMap);

	/// <summary>
	/// Call the HandleMapBoundary function of the map if it exists
	/// </summary>
	/// <param name="PlayerCharacter"></param>
	/// <param name="ViewBox"></param>
	void HandleMapBoundary(AActor* PlayerCharacter, FBox& ViewBox) const;

private:
	ToroidalMapManager() = default;

	AToroidalMap* Map;
};
