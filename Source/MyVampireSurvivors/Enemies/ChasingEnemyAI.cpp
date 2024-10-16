// Fill out your copyright notice in the Description page of Project Settings.


#include "ChasingEnemyAI.h"
#include "ToroidalMaps/ToroidalWorldSystem.h"

void AChasingEnemyAI::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	ToroidalWorldSystem = FToroidalWorldSystem::GetCurrent<UToroidalWorldSystem>(GetWorld());
}

void AChasingEnemyAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ChasePlayer();
}

void AChasingEnemyAI::ChasePlayer()
{
	if (PlayerPawn)
	{
		const FVector VirtualDestination = CalculateVirtualDestination(PlayerPawn->GetActorLocation());
		const float AcceptanceRadius = 5.0f;
		const bool bStopOnOverlap = true;
		const bool bUsePathfinding = false;
		MoveToLocation(VirtualDestination, AcceptanceRadius, bStopOnOverlap, bUsePathfinding);
	}
}

FVector AChasingEnemyAI::CalculateVirtualDestination(const FVector& Destination) const
{
	if (ToroidalWorldSystem == nullptr)
	{
		return Destination;
	}

	const FVector EnemyPosition = GetPawn()->GetActorLocation();
	const FVector Displacement = ToroidalWorldSystem->CalculateDisplacement(EnemyPosition, Destination);
	const FVector VirtualDestination = EnemyPosition + Displacement;

	return VirtualDestination;
}
