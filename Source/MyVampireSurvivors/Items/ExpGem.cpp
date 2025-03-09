// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ExpGem.h"

#include "Items/HomingItemMovementComponent.h"
#include "Players/MyVamSurPlayerController.h"
#include "Players/PlayerCharacter.h"
#include "ToroidalMaps/ToroidalNPAComponent.h"

AExpGem::AExpGem()
{
	HomingItemMovementComponent = CreateDefaultSubobject<UHomingItemMovementComponent>(TEXT("HomingItemMovementComponent"));
	HomingItemMovementComponent->HomingAccelerationMagnitude = 1000000.0f;
	HomingItemMovementComponent->MaxSpeed = 300.0f;
}

void AExpGem::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (HomingItemMovementComponent)
	{
		HomingItemMovementComponent->UpdatedComponent = RootComponent;
	}
}

void AExpGem::BeginPlay()
{
	Super::BeginPlay();

	if (HomingItemMovementComponent == nullptr)
	{
		return;
	}

	if (UWorld* World = GetWorld())
	{
		if (AMyVamSurPlayerController* PlayerController = World->GetFirstPlayerController<AMyVamSurPlayerController>())
		{
			if (APawn* Pawn = PlayerController->GetPawn())
			{
				HomingItemMovementComponent->HomingTargetComponent = Pawn->GetRootComponent();
			}
		}
	}
}

void AExpGem::OnPicked(APlayerCharacter* PlayerCharacter)
{
	PlayerCharacter->AddExp(ExpAmount);

	Super::OnPicked(PlayerCharacter);
}
