// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
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
	 * Check if the player and the view box escape the map and move them to the other side if they are.
	 * 
	 * @param PlayerCharacter - Player character
	 */
	void HandleMapBoundary(APlayerCharacter* PlayerCharacter) const;

	/**
	 * Return the range of the map. 
	 * 
	 * @return Axis-aligned bounding box of the map.
	 */
	const FBox GetMapRange() const;

protected:
	/**
	 * Tile map asset for background.
	 */
	UPROPERTY(EditAnywhere, Category = "Background")
	UPaperTileMap* BackgroundTileMap;

	/**
	 * Background component for toroidal map.
	 */
	UPROPERTY(EditAnywhere, Category = "Background")
	UToroidalMapBackgroundComponent* BackgroundComponent;

	/**
	 * Toroidal space component for toroidal map.
	 */
	UPROPERTY(EditAnywhere, Category = "ToroidalSpace")
	UToroidalSpaceComponent* ToroidalSpaceComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	/**
	 * Check if background tile map asset is changed.
	 * 
	 * @param PropertyChangedEvent - Property changed event
	 */
	bool IsBackgroundTileMapChanged(FPropertyChangedEvent& PropertyChangedEvent) const;
};
