// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ChasingEnemyAI.generated.h"

/**
 * 
 */
UCLASS()
class MYVAMPIRESURVIVORS_API AChasingEnemyAI : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	APawn* PlayerPawn;
};
