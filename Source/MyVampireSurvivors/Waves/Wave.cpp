 // Fill out your copyright notice in the Description page of Project Settings.


#include "Wave.h"

#include "Enemies/Enemy.h"
#include "Enemies/EnemySpawner.h"
#include "GameModes/MyVamSurGameMode.h"
#include "MyVamSurLogChannels.h"
#include "Waves/WaveDefinition.h"

AWave::AWave(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void AWave::Trigger(const TArray<FWaveActorsToSpawn>& WaveSpawningActors)
{
	AEnemySpawner* Spawner = FindSpawner();
	for (const auto& WaveSpawningActor : WaveSpawningActors)
	{
		for (int i = 0; i < WaveSpawningActor.Count; ++i)
		{
			TSubclassOf<AEnemy> EnemyClass(WaveSpawningActor.ActorToSpawn);
			AEnemy* SpawnedEnemy = Spawner->SpawnEnemy(EnemyClass);
			SpawnedEnemy->OnEnemyDied.AddDynamic(this, &ThisClass::HandleSpawnActorDestroyed);
			SpawnedActors.Add(SpawnedEnemy);
		}
	}
}

AEnemySpawner* AWave::FindSpawner() const
{
	UWorld* World = GetWorld();
	check(World);

	AMyVamSurGameMode* GameMode = World->GetAuthGameMode<AMyVamSurGameMode>();
	check(GameMode);

	return GameMode->GetEnemySpawner();
}

void AWave::HandleSpawnActorDestroyed(AEnemy* Actor)
{
	if (SpawnedActors.Contains(Actor))
	{
		SpawnedActors.Remove(Actor);
	}

	if (SpawnedActors.Num() == 0)
	{
		ClearWave();
	}
}

void AWave::ClearWave()
{
	UE_LOG(LogMyVamSur, Warning, TEXT("Wave Cleared: %s"), *GetName());
	OnWaveCleared.Broadcast(this);
	Destroy();
}
