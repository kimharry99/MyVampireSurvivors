// Fill out your copyright notice in the Description page of Project Settings.


#include "ToroidCharacterMovementComponent.h"

#include "DrawDebugHelpers.h"

#include "MyVamSurLogChannels.h"
#include "Players/PlayerCharacter.h"
#include "ToroidalWorldSystem.h"

void UToroidCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* World = GetWorld())
	{
		ToroidalWorldSystem = FToroidalWorldSystem::GetCurrent<UToroidalWorldSystem>(World);
	}
}

void UToroidCharacterMovementComponent::OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity)
{
	Super::OnMovementUpdated(DeltaSeconds, OldLocation, OldVelocity);

	if (!ToroidalWorldSystem.IsValid())
	{
		return;
	}

	if (UpdatedComponent)
	{
		const FVector CurrentLocation = UpdatedComponent->GetComponentLocation();
		const FVector RefinedLocation = ToroidalWorldSystem->RefineLocation(CurrentLocation, false);
		if (CurrentLocation != RefinedLocation)
		{
			UpdatedComponent->SetWorldLocation(RefinedLocation, false, nullptr, ETeleportType::TeleportPhysics);
		}
	}

	if (const APlayerCharacter* PlayerCharacter = GetOwner<APlayerCharacter>())
	{
		ToroidalWorldSystem->SetDistortionZone(FBox::BuildAABB(UpdatedComponent->GetComponentLocation(), PlayerCharacter->GetViewBox().GetExtent()));

#if WITH_EDITOR
		for (const FBox2D& DistortionZone : ToroidalWorldSystem->GetDistortionZones())
		{
			FVector Center = FVector(DistortionZone.GetCenter().X, DistortionZone.GetCenter().Y, 0.0);
			FVector Extent = FVector(DistortionZone.GetExtent().X, DistortionZone.GetExtent().Y, 50.0);
			DrawDebugBox(GetWorld(), Center, Extent, FColor::Red, false, 0.01f, 0, 20.f);
		}
# endif // WITH_EDITOR
	}
}
