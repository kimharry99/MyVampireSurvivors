// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Kismet/GameplayStatics.h"
#include "ToroidalMap.h"

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

void AEnemySpawner::SpawnEnemies(TSubclassOf<AEnemy> EnemyClass, int EnemyCount) const
{
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		for (int i = 0; i < EnemyCount; ++i)
		{
			// Set spawn location
			FVector SpawnLocation = FMath::RandPointInBox(SpawnBoundary);
			SpawnLocation.Z = 50.0f;

			// Spawn an enemy
			AEnemy* Enemy = World->SpawnActor<AEnemy>(EnemyClass, SpawnLocation, FRotator::ZeroRotator);
		}
	}
}
