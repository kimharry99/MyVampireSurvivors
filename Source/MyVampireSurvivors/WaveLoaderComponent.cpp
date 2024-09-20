// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveLoaderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnemySpawner.h"
#include "WaveTableRow.h"

// Sets default values for this component's properties
UWaveLoaderComponent::UWaveLoaderComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWaveLoaderComponent::OnRegister()
{
	Super::OnRegister();

	// Create subobject after Actor that owns this component is created
	WaveFactory = NewObject<UWaveFactory>(this, TEXT("WaveFactory"));
}

void UWaveLoaderComponent::BeginPlay()
{
	Super::BeginPlay();

	// Find EnemySpawner in the level
	if (UWorld* World = GetWorld())
	{
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawner::StaticClass(), FoundActors);
		check(FoundActors.Num() > 0);

		AEnemySpawner* EnemySpawner = Cast<AEnemySpawner>(FoundActors[0]);
		WaveFactory->SetEnemySpawner(EnemySpawner);
	}
}

UWaveList* UWaveLoaderComponent::LoadWavesFromDataTable(UDataTable* InWaveDataTable) const
{
	check(InWaveDataTable);
	UWaveList* WaveList = NewObject<UWaveList>(this->GetOwner());

	// Use UE5 source code
	for (TMap<FName, uint8*>::TConstIterator RowMapIter(InWaveDataTable->GetRowMap().CreateConstIterator()); RowMapIter; ++RowMapIter)
	{
		FWaveTableRow* WaveRecord = reinterpret_cast<FWaveTableRow*>(RowMapIter.Value());

		check(WaveRecord->WaveDataAsset != nullptr);
		UWave* Wave = WaveFactory->CreateWave(WaveRecord->WaveDataAsset);
		if (Wave)
		{
			WaveList->Add(Wave);
		}
	}

	return WaveList;
}
