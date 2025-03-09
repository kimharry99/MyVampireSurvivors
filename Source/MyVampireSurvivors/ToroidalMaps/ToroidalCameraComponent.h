// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "ToroidalCameraComponent.generated.h"

/**
 * 
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UToroidalCameraComponent : public UCameraComponent
{
	GENERATED_BODY()

public:
	UToroidalCameraComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	const FBox GetWorldViewBox() const;

protected:
	//~UActorComponent interface
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//~End of UActorComponent interface

private:
	/** View box defined in camera space. */
	FBox ViewBox;
	/** View box defined in world space. */
	FBox WorldViewBox;

private:
	void InitializeViewBox();
	void UpdateViewBox();
	
};
