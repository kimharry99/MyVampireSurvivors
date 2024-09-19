// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "PaperTileMap.h"
#include "PaperTileMapComponent.h"
#include "ToroidalMapBackgroundComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYVAMPIRESURVIVORS_API UToroidalMapBackgroundComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	/**
	 * @param BackgroundTileMap Tile map asset for background.
	 */
	UToroidalMapBackgroundComponent();

	/**
	 * Get background bounding box.
	 * 
	 * @return Axis-aligned bounding box of background tile map.
	 */
	const FBox GetBackgroundBoundingBox() const;

	/**
	 * Set background tile map asset.
	 * 
	 * @param BackgroundTileMap - Tile map asset for background.
	 */
	void SetBackgroundTileMap(UPaperTileMap* BackgroundTileMap);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void OnRegister() override;


	/**
	 * Tile map component for background.
	 */
	UPROPERTY(EditAnywhere, Category = "Background")
	UPaperTileMapComponent* BackgroundTileMapComponent;

	/**
	 * Tile map component for background margin.
	 */
	UPROPERTY()
	UPaperTileMapComponent* BackgroundMarginTileMapComponent;

private:
	/**
	 * Initialize background tile map component.
	 * 
	 * Create background margin tile map asset from original tile map.
	 * Move it to enclose original tile map.
	 */
	void InitializeBackgroundMarginTileMapComponent();

	/**
	 * Create margin tile map from original tile map and attach to the tile map component.
	 */
	void CreateBackgroundMarginTileMapAndAttach();

	/**
	 * Set format of background margin tile map from background tile map.
	 * 
	 * Set tile width, tile height, pixels per unreal unit, map width and map height.
	 */
	void SetBackgroundMarginTileMapFormat();

	/**
	 * Fill margin tile map from edge tiles of original tile map.
	 */
	void FillMarginTilesFromOriginal();

	/**
	 * Move background margin tile map component to enclose original tile map.
	 */
	void MoveBackgroundMarginTileMapComponent();

	/**
	 * Convert legnth defined with Unreal Unit to number of tiles.
	 * 
	 * @param UnrealUnitLength Length in unreal units.
	 * @param TileMap Tile map asset.
	 * 
	 * @return Length in tile count.
	 */
	const FIntVector2 ConvertUnrealUnitLengthToTileCount(const FVector2D& UnrealUnitLength, UPaperTileMap* TileMap) const;

	/**
	 * Get length of background margin from main camera.
	 * 
	 * @return Length of background margin. It depends on the main camera's view range.
	 *         If main camera is missing, return fixed value.
	 */
	const FVector2D GetMarginLengthFromMainCamera() const;

	/**
	 * Get character follow camera.
	 * 
	 * @return Character follow camera if it exists. Otherwise, return nullptr.
	 */
	const UCameraComponent* GetCharacterFollowingCamera() const;

	/*
	 * Get margin length from camera parameters.
	 * 
	 * @param OrthogonalWidth Width of orthographic view.
	 * @param AspectRatio Aspect ratio of the view.
	 * 
	 * @return Length of margin. X is half of orthogonal width and Y is half of orthogonal height.
	 */
	const FVector2D GetMarginLengthFromCameraParameter(const float OrthogonalWidth, const float AspectRatio) const;

	/**
	 * Get offset of background margin tile map component.
	 * 
	 * @return Offset of background margin tile map component.
	 */
	const FVector GetBackgroundMarginTileMapComponentOffset() const;
};
