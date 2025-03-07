// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
struct MYVAMPIRESURVIVORS_API FCollisionShapeWithTransform
{
	FCollisionShape CollisionShape;
	FQuat Rotation;
	FVector Location;
};
