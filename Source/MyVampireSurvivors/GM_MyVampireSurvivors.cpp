// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_MyVampireSurvivors.h"
#include "ToroidalMapManager.h"
#include "ToroidalMap.h"
#include "Kismet/GameplayStatics.h"

/// <summary>
/// Find a toroidal map in the level and initialize the toroidal map manager
/// </summary>
void AGM_MyVampireSurvivors::StartPlay()
{
	Super::StartPlay();

	// Get map in level
	AToroidalMap* Map = Cast<AToroidalMap>(UGameplayStatics::GetActorOfClass(GetWorld(), AToroidalMap::StaticClass()));
	
	// Initialize toroidal map manager
	ToroidalMapManager::GetInstance()->Initialize(Map);
}
