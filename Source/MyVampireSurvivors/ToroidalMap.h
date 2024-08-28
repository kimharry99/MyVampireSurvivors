// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Actor.h"
#include "PaperTileMapComponent.h"
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
	/// <summary>
	/// Root component of the actor
	/// </summary>
	UPROPERTY(BlueprintReadOnly, Category = "Background")
	USceneComponent* BackgroundRoot;

	/// <summary>
	/// Tile map component for the background
	/// </summary>
	UPROPERTY(EditAnywhere, Category = "Background")
	UPaperTileMapComponent* Background;

	/// <summary>
	/// Tile map component for margin
	/// </summary>
	UPROPERTY(EditAnywhere, Category = "Background")
	UPaperTileMapComponent* MarginTileMap;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#if WITH_EDITOR
	/// <summary>
	/// Create margin tile map from original tile map
	/// </summary>
	UFUNCTION(CallInEditor, Category = "Background")
	void CreateMarginTileMap();
#endif // WITH_EDITOR

private:
	/// <summary>
	/// Margin of the map
	/// </summary>
	float XMargin = 0.0f;
	/// <summary>
	/// Margin of the map
	/// </summary>
	float YMargin = 0.0f;
	/// <summary>
	/// Range of the map
	/// </summary>
	FBox MapRange = FBox(EForceInit::ForceInitToZero);

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

	/**
	 * Set margin value member from camera setting.
	 */
	void SetUpMarginFromCameraSetting();
};
