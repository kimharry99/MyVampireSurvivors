// Fill out your copyright notice in the Description page of Project Settings.


#include "ToroidCharacterMovementComponent.h"

#include "MyVamSurLogChannels.h"
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

	// TODO: Implement NPC logic case
	if (!bIsPlayingCharacter || !ToroidalWorldSystem.IsValid())
	{
		return;
	}

	if (UpdatedComponent)
	{
		const FVector CurrentLocation = UpdatedComponent->GetComponentLocation();
		const FVector RefinedLocation = ToroidalWorldSystem->WrapPosition3D(CurrentLocation);
		if (CurrentLocation == RefinedLocation)
		{
			return;
		}

		UpdatedComponent->SetWorldLocation(RefinedLocation, false, nullptr, ETeleportType::TeleportPhysics);
	}
}
