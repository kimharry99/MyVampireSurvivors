// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/MyVamSurCameraComponent.h"

UMyVamSurCameraComponent::UMyVamSurCameraComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	ProjectionMode = ECameraProjectionMode::Orthographic;
	OrthoWidth = 1024.0f;
}

void UMyVamSurCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeViewBox();
}

void UMyVamSurCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateViewBox();
}

const FBox UMyVamSurCameraComponent::GetWorldViewBox() const
{
	return WorldViewBox;
}

void UMyVamSurCameraComponent::InitializeViewBox()
{
	const float HalfWidth = OrthoWidth * 0.5f;
	const float HalfHeight = HalfWidth / AspectRatio;

	const FVector BoxMin = FVector::ForwardVector * OrthoNearClipPlane + FVector::RightVector * (-HalfWidth) + FVector::UpVector * (-HalfHeight);
	const FVector BoxMax = FVector::ForwardVector * OrthoFarClipPlane + FVector::RightVector * HalfWidth + FVector::UpVector * HalfHeight;

	ViewBox = FBox(BoxMin, BoxMax);
}

void UMyVamSurCameraComponent::UpdateViewBox()
{
	const FVector CameraLocation = GetComponentLocation();
	const FRotator CameraRotation = GetComponentRotation();
	FTransform CameraToWorld(CameraRotation, CameraLocation);

	WorldViewBox = ViewBox.TransformBy(CameraToWorld);
}
