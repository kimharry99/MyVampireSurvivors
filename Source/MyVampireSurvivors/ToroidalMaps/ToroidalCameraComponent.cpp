// Fill out your copyright notice in the Description page of Project Settings.


#include "ToroidalMaps/ToroidalCameraComponent.h"

#include "GameFramework/Character.h"

#include "ToroidalWorldSystem.h"
#include "MyVamSurLogChannels.h"

UToroidalCameraComponent::UToroidalCameraComponent()
{
	ProjectionMode = ECameraProjectionMode::Orthographic;
	OrthoWidth = 1024.0f;
}

const FBox UToroidalCameraComponent::GetWorldViewBox() const
{
	return WorldViewBox;
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
	const float HalfWidth = OrthoWidth * 0.5f;
	const float HalfHeight = HalfWidth / AspectRatio;

	const FVector BoxMin = FVector::ForwardVector * OrthoNearClipPlane + FVector::RightVector * (-HalfWidth) + FVector::UpVector * (-HalfHeight);
	const FVector BoxMax = FVector::ForwardVector * OrthoFarClipPlane + FVector::RightVector * HalfWidth + FVector::UpVector * HalfHeight;

	ViewBox = FBox(BoxMin, BoxMax);
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
