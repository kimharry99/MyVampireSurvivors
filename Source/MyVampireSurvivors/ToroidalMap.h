// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ToroidalMap.generated.h"

UCLASS()
class MYVAMPIRESURVIVORS_API AToroidalMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AToroidalMap();

	/// <summary>
	/// Check if the player and the view box escape the map and move them to the other side if they are
	/// </summary>
	/// <param name="PlayerCharacter"></param>
	/// <param name="ViewBox">View range of the main camera</param>
	void HandleMapBoundary(AActor* PlayerCharacter, FBox& ViewBox) const;

protected:
	UPROPERTY(EditAnywhere, Category = "Map")
	UStaticMeshComponent* Plane;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform) override;

private:
	/// <summary>
	/// Margin of the map
	/// </summary>
	float XMargin;
	/// <summary>
	/// Margin of the map
	/// </summary>
	float YMargin;
	/// <summary>
	/// Range of the map
	/// </summary>
	FBox MapRange;

	/// <summary>
	/// Returns corresponding regions of given box in the toroidal map.
	/// </summary>
	/// <param name="OutRegions"> Array of corresponding regions of the input box in toroidal map.</param>
	/// <param name="Box">Box for which to find the corresponding region.</param>
	void GetCorrespondingRegions(TArray<FBox>& OutRegions, const FBox& Box) const;

	/// <summary>
	/// Transfer actors in source regions to destination region.
	/// </summary>
	/// <param name="SourceRegions">Regions which the actors to move are located.</param>
	/// <param name="Destination">Region to which actors will be moved.</param>
	void TransferObjectsFromMultiSource(const TArray<FBox>& SourceRegions, const FBox& Destination) const;

	/// <summary>
	/// Transfer actors in source region to destination region.
	/// </summary>
	/// <param name="Source">Region which the actors move are located.</param>
	/// <param name="Destination">Region to which actors will be moved.</param>
	/// <param name="QueryChannel">Collision channel for the query.</param>
	void TransferObjects(const FBox& Source, const FBox& Destination, const ECollisionChannel& QueryChannel = ECollisionChannel::ECC_Pawn) const;
};
