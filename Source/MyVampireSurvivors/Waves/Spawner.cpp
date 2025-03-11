// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"

#include "Kismet/GameplayStatics.h"

#include "ToroidalMaps/ToroidalMap.h"

void ASpawner::BeginPlay()
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

AActor* ASpawner::SpawnActorAtRandomInMap(TSubclassOf<AActor> ActorClass)
{
	if (UWorld* World = GetWorld())
	{
		// Set spawn location
		FVector SpawnLocation = FMath::RandPointInBox(SpawnBoundary);
		SpawnLocation.Z = 50.0f;

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		// Spawn an enemy
		return World->SpawnActor<AActor>(ActorClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
	}

	return nullptr;
}
