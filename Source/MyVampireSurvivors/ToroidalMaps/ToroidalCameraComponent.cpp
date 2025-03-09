// Fill out your copyright notice in the Description page of Project Settings.


#include "ToroidalMaps/ToroidalCameraComponent.h"

#include "GameFramework/Character.h"

#include "MyVamSurLogChannels.h"
#include "ToroidalWorldSystem.h"

UToroidalCameraComponent::UToroidalCameraComponent()
{
	ProjectionMode = ECameraProjectionMode::Orthographic;
	OrthoWidth = 1024.0f;
}

void UToroidalCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* World = GetWorld())
	{
		ToroidalWorldSystem = FToroidalWorldSystem::GetCurrent<UToroidalWorldSystem>(World);
	}
	InitializeViewBox();

	if (ACharacter* CharacterOwner = GetOwner<ACharacter>())
	{
		CharacterOwner->OnCharacterMovementUpdated.AddDynamic(this, &ThisClass::OnMovementUpdated);
	}
}

void UToroidalCameraComponent::InitializeViewBox()
{
	const FVector Extent(OrthoFarClipPlane - OrthoNearClipPlane, OrthoWidth, OrthoWidth / AspectRatio);
	ViewBox = FBox::BuildAABB(FVector::ZeroVector, Extent);

	UpdateViewBox();
}

void UToroidalCameraComponent::UpdateViewBox()
{
	const FVector CameraLocation = GetComponentLocation();
	const FRotator CameraRotation = GetComponentRotation();
	FTransform CameraToWorld(CameraRotation, CameraLocation);

	WorldViewBox = ViewBox.TransformBy(CameraToWorld);
}

void UToroidalCameraComponent::OnMovementUpdated(float DeltaSeconds, FVector OldLocation, FVector OldVelocity)
{
	UpdateViewBox();
	if (ToroidalWorldSystem.IsValid())
	{
		ToroidalWorldSystem->SetDistortionZone(WorldViewBox);
#if WITH_EDITOR
		for (const FBox2D& DistortionZone : ToroidalWorldSystem->GetDistortionZones())
		{
			FVector Center = FVector(DistortionZone.GetCenter().X, DistortionZone.GetCenter().Y, 0.0);
			FVector Extent = FVector(DistortionZone.GetExtent().X, DistortionZone.GetExtent().Y, 50.0);
			DrawDebugBox(GetWorld(), Center, Extent, FColor::Red, false, -1.0f, 0, 20.f);
			DrawDebugBox(GetWorld(), Center, Extent, FColor::Red, false, 0.01f, 0, 20.f);
		}
# endif // WITH_EDITOR
	}
}
