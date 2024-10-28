// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ToroidalMaps/ToroidalActorComponent.h"
#include "ToroidalNPAComponent.generated.h"

class APlayerCharacter;

/**
 * Component for Non-Player Actors in a toroidal map.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UToroidalNPAComponent : public UToroidalActorComponent
{
	GENERATED_BODY()

protected:
	//~UActorComponent interface
	virtual void BeginPlay() override;
	//~End of UActorComponent interface

	//~UToroidalActorComponent interface
	virtual void RepositionActor() override;
	//~End of UToroidalActorComponent interface

private:
	/** Cached player character. */
	UPROPERTY()
	TObjectPtr<const APlayerCharacter> Player;

	FBox CalculatePlayerSight(const APlayerCharacter* PlayerCharacter) const;

	/**
	 * Retrns true, if the actor is in the player's sight.
	 */
	bool IsActorInPlayerSight() const;

	/**
	 * Returns true, if the actor is in the player's sight at toroidal toplogy.
	 */
	bool IsActorInToroidalPlayerSight() const;

	/**
	 * Reposition the actor using the player location as the toroidal map origin.
	 */
	void RepositionActorUsingPlayerAsOrigin();
};
