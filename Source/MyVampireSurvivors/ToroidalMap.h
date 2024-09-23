// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperTileMap.h"
#include "PlayerCharacter.h"
#include "ToroidalMapBackgroundComponent.h"
#include "ToroidalSpaceComponent.h"
#include "ToroidalMap.generated.h"

UCLASS()
class MYVAMPIRESURVIVORS_API AToroidalMap : public AActor
{
	GENERATED_BODY()
	
public:
	AToroidalMap();

	/**
	 * Return the range of the map. 
	 * 
	 * @return Axis-aligned bounding box of the map.
	 */
	const FBox GetMapRange() const;

protected:
	/**
	 * Background component for toroidal map.
	 */
	UPROPERTY(EditAnywhere, Category = "Background")
	UToroidalMapBackgroundComponent* BackgroundComponent;

	/**
	 * Toroidal space component for toroidal map.
	 */
	UPROPERTY(VisibleAnyWhere, Category = "ToroidalSpace")
	UToroidalSpaceComponent* ToroidalSpaceComponent;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	/**
	 * Check if the player and the view box escape the map and move them to the other side if they are.
	 */
	void HandleActorsOnToroidalMap() const;

	UPROPERTY()
	TObjectPtr<APlayerCharacter> PlayerCharacter;
};
