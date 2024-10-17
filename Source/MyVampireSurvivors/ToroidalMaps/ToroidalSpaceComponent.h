// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Physics/MyVamSurCollisionChannels.h"
#include "Players/PlayerCharacter.h"
#include "ToroidalSpaceComponent.generated.h"


/**
 * Manage position of actors in toroidal space.
 * The position will be determined by position of player character and its following camera view box.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYVAMPIRESURVIVORS_API UToroidalSpaceComponent_Deprecated : public UActorComponent
{
	GENERATED_BODY()

public:
	UToroidalSpaceComponent_Deprecated();

	/**
	 * Reposition actors to their valid position in toroidal space.
	 * Use position of player character and its following camera view box to determine the position.
	 * 
	 * @param PlayerCharacter - Player character
	 */
	void RepositionActorsInToroidalSpace(APlayerCharacter* PlayerCharacter) const;

	/**
	 * Set space boundary of space.
	 * 
	 * @param NewSpaceBoundary - Boundary of toroidal space in world.
	 */
	void SetSpaceBoundary(const FBox& NewSpaceBoundary);

private:
	/**
	 * Boundary of toroidal space in world.
	 */
	FBox SpaceBoundary;

	/** Handle player escape from space.
	 * 
	 * @param PlayerCharacter - Player character
	 */
	void HandlePlayerEscapingSpace(APlayerCharacter* PlayerCharacter) const;

	/**
	 * Handle player view box escape from space.
	 * 
	 * @param PlayerViewBox - View box of player character following camera
	 */
	void HandlePlayerViewBoxEscapingSpace(const FBox& PlayerViewBox) const;

	/**
	 * Move actors in box to opposite side of space boundary.
	 * 
	 * @param DepartureBox - The box where actors to move are located
	 */
	void MoveActorsInBoxToOppositeSide(const FBox& DepartureBox) const;

	/**
	 * Move actors in corresponding regions to the box.
	 * 
	 * @param DestinationBox - Target box where actors in corresponding regions of the box will be arrived
	 */
	void MoveActorsInCorrespondingRegionsToBox(const FBox& DestinationBox) const;

private:
	/**
	 * Flags for directions in which box escpae boundary.
	 */
	enum EEscapeDirection: uint8
	{
		Left   = 1 << 0,    // 0001
		Right  = 1 << 1,    // 0010
		Top    = 1 << 2,    // 0100
		Bottom = 1 << 3,    // 1000
	};

	/**
	 * Corresponding region offset for each escape flags.
	 */
	struct FCorrespondingRegionOffset
	{
		uint8 EscapeFlags;   // Flags for out-of-boundary direction of source region
		FVector Offset;      // Offset from source region to corresponding region
	};

	/**
	 * Sign fo corresponding region offsets for each escape direction.
	 * 
	 * @param Escape direction
	 * @param Sign of offset vector from source region to corresponding region.
	 * The sign will be multiplied by width and height of space boundary to get the offset
	 */
	TMap<uint8, FVector> OffsetSignOfCorrespondingRegions = {
		  { EEscapeDirection::Left, FVector(1.0f, 0.0f, 0.0f) },
		  { EEscapeDirection::Right, FVector(-1.0f, 0.0f, 0.0f) },
		  { EEscapeDirection::Top, FVector(0.0f, 1.0f, 0.0f) },
		  { EEscapeDirection::Bottom, FVector(0.0f, -1.0f, 0.0f) },
		  { EEscapeDirection::Left | EEscapeDirection::Top, FVector(1.0f, 1.0f, 0.0f) },
		  { EEscapeDirection::Right | EEscapeDirection::Top, FVector(-1.0f, 1.0f, 0.0f) },
		  { EEscapeDirection::Left | EEscapeDirection::Bottom, FVector(1.0f, -1.0f, 0.0f) },
		  { EEscapeDirection::Right | EEscapeDirection::Bottom, FVector(-1.0f, -1.0f, 0.0f) }
	};

	/**
	 * Compute corresponding regions of given box in toroidal space.
	 * 
	 * @param OutCorrespondingRegions - Array of corresponding regions of the input box in toroidal space
	 * @param Region - The region determined with box to compute corresponding regions
	 */
	void ComputeCorrespondingRegionsInToroidalSpace(TArray<FBox>& OutCorrespondingRegions, const FBox& Region) const;

	/**
	 * Compute escape flag of the box from the boundary.
	 * 
	 * @param Box - Box to compute escape flags
	 * @param Boundary - Boundary to check escape 
	 * @return Escape flag of the box from the boundary
	 */
	const uint8 ComputeBoxEscapeFlag(const FBox& Box, const FBox& Boundary) const;

	/**
	 * Find a box inside the bound.
	 * Implemented to return pointer of box for handling error case.
	 *
	 * @param Boxes - Array of boxes
	 * @param Bound - The bound to find a box inside
	 * @return Pointer of box that center is inside the bound. Return nullptr if not found.
	 */
	const FBox* FindBoxInsideBound(const TArray<FBox>& Boxes, const FBox& Bound) const;

	/**
	 * Transfer actors in source regions to destination region.
	 * 
	 * @param SourceRegions - Regions which the actors to move are located
	 * @param Destination - Region to which actors will be moved
	 */
	void TransferObjectsFromMultiSource(const TArray<FBox>& SourceRegions, const FBox& Destination) const;

	/**
	 * Transfer actors in source region to destination region.
	 * 
	 * @param Source - The region which the actors move are located
	 * @param Destination - The region to which actors will be moved
	 * @param TraceChannel - Trace channel for the query
	 */
	void TransferObjects(const FBox& Source, const FBox& Destination, const ECollisionChannel& TraceChannel = TraceChannel_ToroidalWorld) const;
};
