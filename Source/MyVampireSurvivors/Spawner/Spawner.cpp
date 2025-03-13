// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"

#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"

#include "Enemies/Enemy.h"
#include "GameModes/MyVamSurGameMode.h"
#include "ObjectPools/ActorPool.h"
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

	InitializeEnemyPool();
}

AActor* ASpawner::SpawnActorAtRandomInMap(TSubclassOf<AActor> ActorClass)
{
	FVector SpawnLocation;
	if (const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(this))
	{
		// Set spawn location
		FNavLocation NavLocation;
		if (NavSystem->GetRandomPointInNavigableRadius(SpawnBoundary.GetCenter(), SpawnBoundary.GetExtent().GetMax(), NavLocation))
		{
			SpawnLocation = NavLocation.Location;
		}
	}
	else
	{
		SpawnLocation = FMath::RandPointInBox(SpawnBoundary);
	}

	return SpawnActor(ActorClass, FTransform(FRotator::ZeroRotator, SpawnLocation));
}

AActor* ASpawner::SpawnActor(TSubclassOf<AActor> ActorClass, FTransform SpawnTransform)
{
	AActor* NewActor = SpawnActorByType(ActorClass);
	if (NewActor)
	{
		FVector SpawnLocation = SpawnTransform.GetLocation();
		SpawnLocation.Z = NewActor->GetComponentsBoundingBox().GetExtent().Z;

		if (UWorld* World = GetWorld())
		{
			World->FindTeleportSpot(NewActor, SpawnLocation, FRotator::ZeroRotator);
		}

		SpawnTransform.SetLocation(SpawnLocation);

		NewActor->SetActorTransform(SpawnTransform, false, nullptr, ETeleportType::TeleportPhysics);
	}

	return NewActor;
}

void ASpawner::InitializeEnemyPool()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	SpawnParams.bHideFromSceneOutliner = true;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	EnemyPool = GetWorld()->SpawnActor<AActorPool>(SpawnParams);
	EnemyPool->SetActorClass(AEnemy::StaticClass());
}

AActor* ASpawner::SpawnActorByType(TSubclassOf<AActor> ActorClass)
{
	check(ActorClass);
	if (ActorClass->IsChildOf(AEnemy::StaticClass()))
	{
		return SpawnEnemy(TSubclassOf<AEnemy>(ActorClass));
	}
	else
	{
		if (UWorld* World = GetWorld())
		{
			return World->SpawnActor<AActor>(ActorClass);
		}
	}

	return nullptr;
}

AEnemy* ASpawner::SpawnEnemy(TSubclassOf<AEnemy> EnemyClass)
{
	if (!EnemyPool)
	{
		return nullptr;
	}

	check(EnemyClass);
	AActor* SpawnedActor = EnemyPool->GetPooledActor();
	if (SpawnedActor)
	{
		AEnemy* SpawnedEnemy = Cast<AEnemy>(SpawnedActor);
		checkf(SpawnedEnemy, TEXT("EnemyPool doesn't create AEnemy instance."));

		SpawnedEnemy->CopyFromActualClass(EnemyClass);
		return SpawnedEnemy;
	}

	return nullptr;
}
