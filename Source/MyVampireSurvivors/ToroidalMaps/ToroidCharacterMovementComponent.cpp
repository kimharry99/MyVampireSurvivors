// Fill out your copyright notice in the Description page of Project Settings.


#include "ToroidCharacterMovementComponent.h"

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
		if (bIsPlayingCharacter)
		{
			if (const APlayerCharacter* PlayerCharacter = GetOwner<APlayerCharacter>())
			{
				ToroidalWorldSystem->SetDistortionZone(PlayerCharacter->GetViewBox());
			}
		}

		const FVector CurrentLocation = UpdatedComponent->GetComponentLocation();
		const FVector RefinedLocation = ToroidalWorldSystem->RefineLocation(CurrentLocation);
		if (CurrentLocation != RefinedLocation)
		{
			UpdatedComponent->SetWorldLocation(RefinedLocation, false, nullptr, ETeleportType::TeleportPhysics);
		}
	}
}
