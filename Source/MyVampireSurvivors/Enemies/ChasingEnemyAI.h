// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ChasingEnemyAI.generated.h"

class UToroidalWorldSystem;

/**
 * 
 */
UCLASS()
class MYVAMPIRESURVIVORS_API AChasingEnemyAI : public AAIController
{
	GENERATED_BODY()

protected:
	//~AActor interface
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	//~End of AActor interface

private:
	UPROPERTY()
	TObjectPtr<APawn> PlayerPawn;

	/**
	 * Chase the player.
	 */
	void ChasePlayer();

	UPROPERTY()
	TObjectPtr<UToroidalWorldSystem> ToroidalWorldSystem;

	/**
	 * Calculate the virtual destination for the enemy to chase the player.
	 * 
	 * @param Destination The destination to chase.
	 * @return The virtual destination.
	 */
	FVector CalculateVirtualDestination(const FVector& Destination) const;
};
