// Fill out your copyright notice in the Description page of Project Settings.


#include "ToroidalMaps/ToroidalActorComponent.h"
#include "ToroidalMaps/ToroidalWorldSystem.h"

UToroidalActorComponent::UToroidalActorComponent()
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
		check(ToroidalWorldSystem);
	}
}

void UToroidalActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	RepositionActor();
}

void UToroidalActorComponent::RepositionActor()
{
	// Empty implementation
}

void UToroidalActorComponent::WrapActorLocation()
{
	if (AActor* Owner = GetOwner())
	{
		FVector NewLocation = GetToroidalWorldSystem()->WrapPosition3D(Owner->GetActorLocation());
		Owner->SetActorLocation(NewLocation, false, nullptr, TeleportType);
	}
}
