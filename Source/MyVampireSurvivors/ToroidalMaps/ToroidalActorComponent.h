// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ToroidalActorComponent.generated.h"

class UToroidalWorldSystem;

/**
 * Component for actors in a toroidal map.
 * Can handle the actor position.
 */
UCLASS(Abstract)
class MYVAMPIRESURVIVORS_API UToroidalActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UToroidalActorComponent();

protected:
	//~UActorComponent interface
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//~End of UActorComponent interface

protected:
	/**
	 * Reposition the actor in the toroidal map.
	 */
	virtual void RepositionActor();

	/**
	 * Wrap the actor location in the toroidal map.
	 */
	void WrapActorLocation();

protected:
	FORCEINLINE UToroidalWorldSystem* GetToroidalWorldSystem() const
	{
		return ToroidalWorldSystem;
	}

	ETeleportType TeleportType = ETeleportType::TeleportPhysics;

private:
	UPROPERTY()
	TObjectPtr<UToroidalWorldSystem> ToroidalWorldSystem;
};
