// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyWave.h"
#include "Kismet/GameplayStatics.h"
#include "EnemySpawnRecord.h"
#include "ToroidalMapManager.h"

UEnemyWave* UEnemyWave::CreateEnemyWave(UWorld* World, const UWaveDataAsset* WaveDataAsset)
{
	const UEnemyWaveDataAsset* EnemyWaveDataAsset = Cast<UEnemyWaveDataAsset>(WaveDataAsset);
	if (EnemyWaveDataAsset == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Wave data asset is not EnemyWaveDataAsset"))
		return nullptr;
	}

	UEnemyWave* EnemyWave = NewObject<UEnemyWave>(World);
	EnemyWave->EnemyWaveDataAsset = EnemyWaveDataAsset;
	return EnemyWave;
}

void UEnemyWave::Trigger()
{
	// FIXME: Separate enemies spawning logic to a separate class
	for (const FEnemySpawnRecord& EnemySpawnRecord : EnemyWaveDataAsset->GetSpawningEnemyGroup())
	{
		UWorld* World = GetWorld();
		if (World == nullptr) return;

		for (int i = 0; i < EnemySpawnRecord.EnemyCount; ++i)
		{
			// Set spawn location
			const FBox& SpawnBoundary = ToroidalMapManager::GetInstance()->GetMapRange();
			FVector SpawnLocation = FMath::RandPointInBox(SpawnBoundary);
			SpawnLocation.Z = 50.0f;

			// Spawn an enemy
			AEnemy* Enemy = World->SpawnActor<AEnemy>(EnemySpawnRecord.EnemyClass, SpawnLocation, FRotator::ZeroRotator);
			
			const FString EnemyName = Enemy->GetName();
			UE_LOG(LogTemp, Warning, TEXT("Spawning enemy: %s"), *EnemyName);
		}
	}
}
