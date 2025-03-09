// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "ToroidalCameraComponent.generated.h"

class UToroidalWorldSystem;

/**
 *
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UToroidalCameraComponent : public UCameraComponent
{
	GENERATED_BODY()

public:
	UToroidalCameraComponent();

protected:
	//~UActorComponent interface
	virtual void BeginPlay() override;
	//~End of UActorComponent interface

private:
	UFUNCTION()
	void OnMovementUpdated(float DeltaSeconds, FVector OldLocation, FVector OldVelocity);

	/** View box defined in camera space. */
	FBox ViewBox;
	/** View box defined in world space. */
	FBox WorldViewBox;

	void InitializeViewBox();
	void UpdateViewBox();

	TWeakObjectPtr<UToroidalWorldSystem> ToroidalWorldSystem;
};
