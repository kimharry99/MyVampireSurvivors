// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ToroidalMaps/ToroidalActorComponent.h"
#include "ToroidalPlayerComponent.generated.h"

/**
 * Component for the player pawn in a toroidal map.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UToroidalPlayerComponent : public UToroidalActorComponent
{
	GENERATED_BODY()

protected:
	//~UToroidalActorComponent interface
	virtual void RepositionActor() override;
	//~End of UToroidalActorComponent interface
};
