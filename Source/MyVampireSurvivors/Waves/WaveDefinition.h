// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WaveDefinition.generated.h"


USTRUCT(BlueprintType)
struct MYVAMPIRESURVIVORS_API FWaveActorsToSpawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Wave")
	TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere, Category = "Wave")
	int Count = 0;
};


/**
 * 
 */
UCLASS(Const, BlueprintType, ClassGroup = "Wave")
class MYVAMPIRESURVIVORS_API UWaveDefinition : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	TArray<FWaveActorsToSpawn> ActorsToSpawn;
};
