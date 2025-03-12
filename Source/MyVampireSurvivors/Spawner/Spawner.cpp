// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"

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
	check(ActorClass);
	AActor* NewActor = SpawnActorByType(ActorClass);
	if (NewActor)
	{
		// Set spawn location
		FVector SpawnLocation = FMath::RandPointInBox(SpawnBoundary);
		SpawnLocation.Z = 50.0f;
		NewActor->SetActorLocation(SpawnLocation);
	}

	return NewActor;
}

AActor* ASpawner::SpawnActor(TSubclassOf<AActor> ActorClass, const FTransform& SpawnTransform)
{
	check(ActorClass);
	AActor* NewActor = SpawnActorByType(ActorClass);
	if (NewActor)
	{
		NewActor->SetActorTransform(SpawnTransform);
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
