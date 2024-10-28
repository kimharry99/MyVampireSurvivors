// Fill out your copyright notice in the Description page of Project Settings.


#include "ToroidalNPAComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToroidalMaps/ToroidalWorldSystem.h"
#include "Players/PlayerCharacter.h"

void UToroidalNPAComponent::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	check(World);
	APlayerController* FirstPlayer = World->GetFirstPlayerController();
	check(FirstPlayer);
	Player = FirstPlayer->GetPawn<APlayerCharacter>();
	check(Player);
}

void UToroidalNPAComponent::RepositionActor()
{
	Super::RepositionActor();

	if(IsActorInPlayerSight())
	{
		// Maintain the actor's location.
		return;
	}

	if (IsActorInToroidalPlayerSight())
	{
		RepositionActorUsingPlayerAsOrigin();
	}
	else
	{
		// Update location normally.
		WrapActorLocation();
	}
}

FBox UToroidalNPAComponent::CalculatePlayerSight(const APlayerCharacter* PlayerCharacter) const
{
	if(PlayerCharacter == nullptr)
	{
		return FBox();
	}

	return PlayerCharacter->GetViewBox();
}

void UToroidalNPAComponent::RepositionActorUsingPlayerAsOrigin()
{
	if (AActor* Owner = GetOwner())
	{
		FVector DisplacementToPlayer = GetToroidalWorldSystem()->CalculateDisplacement(Owner->GetActorLocation(), Player->GetActorLocation());

		// NewActorLocation can be outside the toroidal map.
		FVector NewActorLocation = Player->GetActorLocation() - DisplacementToPlayer; // Player + (Actor - Player)
		Owner->SetActorLocation(NewActorLocation, false, nullptr, TeleportType);
	}
}

bool UToroidalNPAComponent::IsActorInPlayerSight() const
{
	if(AActor* Owner = GetOwner())
	{
		FBox ViewBox = CalculatePlayerSight(Player);
		return ViewBox.IsInsideXY(Owner->GetActorLocation());
	}
	return false;
}

bool UToroidalNPAComponent::IsActorInToroidalPlayerSight() const
{
	if (AActor* Owner = GetOwner())
	{
		return GetToroidalWorldSystem()->IsInsideBoxOnTorus(
			Owner->GetActorLocation(),
			CalculatePlayerSight(Player)
		);
	}
	return false;
}
