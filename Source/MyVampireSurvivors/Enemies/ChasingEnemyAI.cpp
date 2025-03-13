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
	if (PlayerPawn == nullptr)
	{
		return;
	}

	if(APawn* ControlledPawn = GetPawn())
	{
		const FVector Destination = PlayerPawn->GetActorLocation();
		MoveToLocation(CalculateVirtualDestination(Destination));
	}
}

FVector AChasingEnemyAI::CalculateVirtualDestination(const FVector& Destination) const
{
	if (ToroidalWorldSystem == nullptr)
	{
		return Destination;
	}

	const FVector EnemyPosition = GetPawn()->GetActorLocation();
	const FVector Displacement = ToroidalWorldSystem->ComputeToroidalDisplacement(EnemyPosition, Destination);
	const FVector VirtualDestination = EnemyPosition + Displacement;

	return VirtualDestination;
}
