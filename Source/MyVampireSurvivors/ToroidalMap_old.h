// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MYVAMPIRESURVIVORS_API ToroidalMap_old
{
public:
	ToroidalMap_old(float InWidth, float InHeight);

	FVector WrapPosition(const FVector& Position) const;

private:
	float Width;
	float Height;
};
