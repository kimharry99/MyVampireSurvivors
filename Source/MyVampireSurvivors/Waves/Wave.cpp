 // Fill out your copyright notice in the Description page of Project Settings.


#include "Wave.h"

#include "Enemies/Enemy.h"
#include "GameModes/MyVamSurGameMode.h"
#include "MyVamSurLogChannels.h"
#include "Waves/WaveParticipantInterface.h"
#include "Waves/Spawner.h"
#include "Waves/WaveDefinition.h"

AWave::AWave(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void AWave::Trigger(const TArray<FWaveActorsToSpawn>& WaveSpawningActors)
{
	ASpawner* Spawner = FindSpawner();
	for (const auto& WaveSpawningActor : WaveSpawningActors)
	{
		for (int i = 0; i < WaveSpawningActor.Count; ++i)
		{
			if (AActor* SpawnedActor = Spawner->SpawnActorAtRandomInMap(WaveSpawningActor.ActorToSpawn))
			{
				if (AEnemy* SpawnedEnemy = CastChecked<AEnemy>(SpawnedActor))
				{
					SpawnedEnemy->OnEnemyDied.AddDynamic(this, &ThisClass::HandleSpawnActorDestroyed);
				}
				if (IWaveParticipantInterface* SpawnedWaveActor = Cast<IWaveParticipantInterface>(SpawnedActor))
				{
					SpawnedWaveActor->GetOnWaveActorDestroyedDelegate()->AddUObject(this, &ThisClass::HandleWaveActorDestroyed);
				}

				SpawnedActors.Add(SpawnedActor);
			}
		}
	}
}

ASpawner* AWave::FindSpawner() const
{
	UWorld* World = GetWorld();
	check(World);

	AMyVamSurGameMode* GameMode = World->GetAuthGameMode<AMyVamSurGameMode>();
	check(GameMode);

	return GameMode->GetSpawner();
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

void AWave::HandleWaveActorDestroyed(IWaveParticipantInterface* WaveActor)
{
	if (SpawnedWaveActors.Contains(WaveActor))
	{
		SpawnedWaveActors.Remove(WaveActor);
	}

	if (SpawnedWaveActors.Num() == 0)
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
