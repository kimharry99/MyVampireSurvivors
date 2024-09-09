// Fill out your copyright notice in the Description page of Project Settings.


#include "ToroidalMapManager.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

ToroidalMapManager* ToroidalMapManager::GetInstance()
{
	static ToroidalMapManager instance;
	return &instance;
}

void ToroidalMapManager::Initialize(AToroidalMap* NewMap)
{
	Map = NewMap;
}

void ToroidalMapManager::HandleMapBoundary(APlayerCharacter* PlayerCharacter) const
{
	Map->HandleMapBoundary(PlayerCharacter);
}

const FBox ToroidalMapManager::GetMapRange() const
{
	return Map->GetMapRange();
}
