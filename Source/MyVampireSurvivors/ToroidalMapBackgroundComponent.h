// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void OnRegister() override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

private:
	/** Tile map asset for background. */
	UPROPERTY(EditDefaultsOnly, Category = "Background", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPaperTileMap> BackgroundTileMap;

	/** Tile map asset for background margin. */
	UPROPERTY(EditDefaultsOnly, Category = "Background", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPaperTileMap> BackgroundMarginTileMap;

	/** Tile map component for background. */
	UPROPERTY()
	TObjectPtr<UPaperTileMapComponent> BackgroundTileMapComponent;

	/** Tile map component for background margin. */
	UPROPERTY()
	TObjectPtr<UPaperTileMapComponent> BackgroundMarginTileMapComponent;

	/** Length of background margin. */
	UPROPERTY(EditAnywhere, Category = "Background")
	float MarginLength = 1024.0f;

	/**
	 * Update background tile map component.
	 * Set tile map asset to the component.
	 */
	void UpdateBackgroundTileMapComponent();

	/**
	 * Update background margin tile map component.
	 * Set tile map asset to the component.
	 * Initialize background margin tile map component if all required assets are valid.
	 */
	void UpdateBackgroundMarginTileMapComponent();

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
	 * Called when background tile map changed.
	 * Update background margin tile map component and save background margin tile map.
	 */
	void PostBackgroundMarginTileMapChanged();

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
	 * Get pair of background margin length.
	 * 
	 * @return Length of background margin.
	 */
	const FVector2D GetMarginLengthPair() const;

	/**
	 * Get offset of background margin tile map component.
	 * 
	 * @return Offset of background margin tile map component.
	 */
	const FVector GetBackgroundMarginTileMapComponentOffset() const;
};
