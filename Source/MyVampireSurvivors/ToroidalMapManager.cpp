// Fill out your copyright notice in the Description page of Project Settings.


#include "ToroidalMapManager.h"

ToroidalMapManager* ToroidalMapManager::GetInstance()
{
	static ToroidalMapManager instance;
	return &instance;
}

void ToroidalMapManager::Initialize(AToroidalMap* NewMap)
{
	Map = NewMap;
}

void ToroidalMapManager::HandleMapBoundary(AActor* PlayerCharacter, FBox& ViewBox) const
{
	Map->HandleMapBoundary(PlayerCharacter, ViewBox);
}
