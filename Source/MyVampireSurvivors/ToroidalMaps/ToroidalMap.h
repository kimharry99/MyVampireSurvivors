// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperTileMap.h"
#include "Players/PlayerCharacter.h"
#include "ToroidalMapBackgroundComponent.h"
#include "ToroidalMap.generated.h"

UCLASS()
class MYVAMPIRESURVIVORS_API AToroidalMap : public AActor
{
	GENERATED_BODY()
	
public:
	AToroidalMap();

protected:
	//~AActor interface
	virtual void BeginPlay() override;
	//~End of AActor interface

protected:
	/**
	 * Background component for toroidal map.
	 */
	UPROPERTY(EditAnywhere, Category = "Background")
	UToroidalMapBackgroundComponent* BackgroundComponent;

public:
	/**
	 * Return the range of the map. 
	 * 
	 * @return Axis-aligned bounding box of the map.
	 */
	const FBox GetMapRange() const;
};
