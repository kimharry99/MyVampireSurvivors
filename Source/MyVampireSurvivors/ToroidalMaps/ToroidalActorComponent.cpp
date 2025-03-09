// Fill out your copyright notice in the Description page of Project Settings.


#include "ToroidalMaps/ToroidalActorComponent.h"

#include "MyVamSurLogChannels.h"
#include "ToroidalMaps/ToroidalWorldSystem.h"

UToroidalActorComponent::UToroidalActorComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PostPhysics;
}

void UToroidalActorComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* World = GetWorld())
	{
		ToroidalWorldSystem = FToroidalWorldSystem::GetCurrent<UToroidalWorldSystem>(World);
	}
}

void UToroidalActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!ToroidalWorldSystem.IsValid())
	{
		return;
	}

	if (AActor* Owner = GetOwner())
	{
		const FVector CurrentLocation = Owner->GetActorLocation();
		const FVector RefinedLocation = ToroidalWorldSystem->RefineLocation(CurrentLocation);
		if (!CurrentLocation.Equals(RefinedLocation))
		{
			Owner->SetActorLocation(RefinedLocation, false, nullptr, ETeleportType::TeleportPhysics);
		}
	}
}

UToroidalActorComponent_Deprecated::UToroidalActorComponent_Deprecated()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PostPhysics;
}

void UToroidalActorComponent_Deprecated::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* World = GetWorld())
	{
		ToroidalWorldSystem = FToroidalWorldSystem::GetCurrent<UToroidalWorldSystem>(World);
		check(ToroidalWorldSystem);
	}
}

void UToroidalActorComponent_Deprecated::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	RepositionActor();
}

void UToroidalActorComponent_Deprecated::RepositionActor()
{
	// Empty implementation
}

void UToroidalActorComponent_Deprecated::WrapActorLocation()
{
	if (AActor* Owner = GetOwner())
	{
		FVector NewLocation = GetToroidalWorldSystem()->WrapPosition3D(Owner->GetActorLocation());
		Owner->SetActorLocation(NewLocation, false, nullptr, TeleportType);
	}
}
