// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyVamSurPlayerState.generated.h"

class UHealthData;

/**
 * 
 */
UCLASS()
class MYVAMPIRESURVIVORS_API AMyVamSurPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AMyVamSurPlayerState();

	UHealthData* GetHealthData() const;

private:
	UPROPERTY()
	TObjectPtr<UHealthData> HealthData;
};
