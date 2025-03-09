// Fill out your copyright notice in the Description page of Project Settings.


#include "ToroidalMaps/ToroidalCameraComponent.h"

UToroidalCameraComponent::UToroidalCameraComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
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

	InitializeViewBox();
}

void UToroidalCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateViewBox();
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
