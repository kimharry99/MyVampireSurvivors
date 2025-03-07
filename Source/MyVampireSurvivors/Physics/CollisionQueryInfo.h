// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
struct MYVAMPIRESURVIVORS_API FCollisionQueryInfo
{
public:
	const FCollisionShape CollisionShape;
	const FQuat Rotation;
	const FVector Location;
	const ECollisionChannel CollisionChannel;
};
