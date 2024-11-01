// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"

#include "Kismet/GameplayStatics.h"

#include "Enemies/Enemy.h"
#include "ToroidalMaps/ToroidalMap.h"

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	// Find toroid map in the map
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AToroidalMap::StaticClass(), FoundActors);
	check(FoundActors.Num() > 0);
	AToroidalMap* ToroidalMap = Cast<AToroidalMap>(FoundActors[0]);

	// Set spawn boundary to map boundary
	check(ToroidalMap != nullptr);
	SpawnBoundary = ToroidalMap->GetMapRange();
}

AEnemy* AEnemySpawner::SpawnEnemy(TSubclassOf<AEnemy> EnemyClass) const
{
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		// Set spawn location
		FVector SpawnLocation = FMath::RandPointInBox(SpawnBoundary);
		SpawnLocation.Z = 50.0f;

		// Spawn an enemy
		return World->SpawnActor<AEnemy>(EnemyClass, SpawnLocation, FRotator::ZeroRotator);
	}

	return nullptr;
}
