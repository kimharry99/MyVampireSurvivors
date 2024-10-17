// Fill out your copyright notice in the Description page of Project Settings.


#include "ToroidalNPAComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToroidalMaps/ToroidalWorldSystem.h"
#include "Players/PlayerCharacter.h"

UToroidalNPAComponent::UToroidalNPAComponent()
{

}

void UToroidalNPAComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
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

void UToroidalNPAComponent::RepositionActorUsingPlayerAsOrigin()
{
	if (AActor* Owner = GetOwner())
	{
		FVector DisplacementToPlayer = GetToroidalWorldSystem()->CalculateDisplacement(Owner->GetActorLocation(), Player->GetActorLocation());
				
		// NewActorLocation can be outside the toroidal map.
		FVector NewActorLocation = Player->GetActorLocation() - DisplacementToPlayer;
		Owner->SetActorLocation(NewActorLocation, false, nullptr, TeleportType);
	}
}

bool UToroidalNPAComponent::IsActorInPlayerSight() const
{
	if(AActor* Owner = GetOwner())
	{
		FBox ViewBox = Player->GetViewBox();
		return ViewBox.IsInsideXY(Owner->GetActorLocation());
	}
	return false;
}

bool UToroidalNPAComponent::IsActorInToroidalPlayerSight() const
{
	if (AActor* Owner = GetOwner())
	{
		return GetToroidalWorldSystem()->IsInsideBoxOnTorus(Owner->GetActorLocation(), Player->GetViewBox());
	}
	return false;
}
