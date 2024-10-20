// Fill out your copyright notice in the Description page of Project Settings.


#include "ToroidalSpaceComponent.h"
#include "MyVamSurLogChannels.h"

UToroidalSpaceComponent_Deprecated::UToroidalSpaceComponent_Deprecated()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	bEditableWhenInherited = false;
}

void UToroidalSpaceComponent_Deprecated::SetSpaceBoundary(const FBox& NewSpaceBoundary)
{
	SpaceBoundary = NewSpaceBoundary;
}

void UToroidalSpaceComponent_Deprecated::RepositionActorsInToroidalSpace(APlayerCharacter* PlayerCharacter) const
{
	// Check player escape space
	if (!SpaceBoundary.IsInsideXY(PlayerCharacter->GetActorLocation()))
	{
		HandlePlayerEscapingSpace(PlayerCharacter);
		return;
	}

	// Check view box escape space
	const FBox PlayerCharacterViewBox = PlayerCharacter->GetViewBox();
	if (!SpaceBoundary.IsInsideXY(PlayerCharacterViewBox))
	{
		HandlePlayerViewBoxEscapingSpace(PlayerCharacterViewBox);
		return;
	}
}

void UToroidalSpaceComponent_Deprecated::HandlePlayerEscapingSpace(APlayerCharacter* PlayerCharacter) const
{
	const FBox ViewBox = PlayerCharacter->GetViewBox();
	MoveActorsInBoxToOppositeSide(ViewBox);
}

void UToroidalSpaceComponent_Deprecated::MoveActorsInBoxToOppositeSide(const FBox& DepartureBox) const
{
	TArray<FBox> PossibleDestinations;
	ComputeCorrespondingRegionsInToroidalSpace(PossibleDestinations, DepartureBox);

	// Only box at opposite side should be inside the bound
	const FBox* DestinationPtr = FindBoxInsideBound(PossibleDestinations, SpaceBoundary);
	if (DestinationPtr != nullptr)
	{	
		TransferObjects(DepartureBox, *DestinationPtr, TraceChannel_ToroidalWorld); // Use ToroidalWorld channel
	}
}

void UToroidalSpaceComponent_Deprecated::HandlePlayerViewBoxEscapingSpace(const FBox& PlayerViewBox) const
{
	MoveActorsInCorrespondingRegionsToBox(PlayerViewBox);
}

void UToroidalSpaceComponent_Deprecated::MoveActorsInCorrespondingRegionsToBox(const FBox& DestinationBox) const
{
	TArray<FBox> CorrespondingRegions;
	ComputeCorrespondingRegionsInToroidalSpace(CorrespondingRegions, DestinationBox);
	TransferObjectsFromMultiSource(CorrespondingRegions, DestinationBox);
}

void UToroidalSpaceComponent_Deprecated::ComputeCorrespondingRegionsInToroidalSpace(TArray<FBox>& OutCorrespondingRegions, const FBox& Region) const
{
	if (Region.Min.X > Region.Max.X || Region.Min.Y > Region.Max.Y)
	{
		UE_LOG(LogMyVamSur, Error, TEXT("Box.Min should be less than Box.Max, Box: %s"), *Region.ToString());
		return;
	}

	uint8 BoxEscapeFlag = ComputeBoxEscapeFlag(Region, SpaceBoundary);

	const float Width = SpaceBoundary.GetExtent().X * 2.0f;
	const float Height = SpaceBoundary.GetExtent().Y * 2.0f;

	OutCorrespondingRegions.Empty();
	for (const TPair<uint8, FVector>& OffsetSign : OffsetSignOfCorrespondingRegions)
	{
		// Check if the box escape in the direction
		if ((BoxEscapeFlag & OffsetSign.Key) == OffsetSign.Key)
		{
			const FVector Offset = FVector(OffsetSign.Value.X * Width, OffsetSign.Value.Y * Height, 0.0f);
			OutCorrespondingRegions.Add(Region.ShiftBy(Offset));
		}
	}
}

const uint8 UToroidalSpaceComponent_Deprecated::ComputeBoxEscapeFlag(const FBox& Box, const FBox& Boundary) const
{
	uint8 EscapeFlags = 0;
	if (Box.Min.X < Boundary.Min.X)
	{
		EscapeFlags |= EEscapeDirection::Left;
	}
	if (Box.Max.X > Boundary.Max.X)
	{
		EscapeFlags |= EEscapeDirection::Right;
	}
	if (Box.Min.Y < Boundary.Min.Y)
	{
		EscapeFlags |= EEscapeDirection::Top;
	}
	if (Box.Max.Y > Boundary.Max.Y)
	{
		EscapeFlags |= EEscapeDirection::Bottom;
	}

	return EscapeFlags;
}

void UToroidalSpaceComponent_Deprecated::TransferObjectsFromMultiSource(const TArray<FBox>& SourceRegions, const FBox& Destination) const
{
	// Traverse all source regions
	for (const FBox& Source : SourceRegions)
	{
		TransferObjects(Source, Destination, TraceChannel_ToroidalWorld); // Use ToroidalWorld channel
	}
}

void UToroidalSpaceComponent_Deprecated::TransferObjects(const FBox& Source, const FBox& Destination, const ECollisionChannel& TraceChannel) const
{
	// Do box trace to get all actors in source regions
	TArray<FOverlapResult> OverlapResults;

	GetWorld()->OverlapMultiByChannel(
		OverlapResults,
		Source.GetCenter(),
		FQuat::Identity,
		TraceChannel,
		FCollisionShape::MakeBox(Source.GetExtent())
	);

	if (OverlapResults.Num() == 0)
	{
		return;
	}

	// Transfer overlapped actors to destination
	FVector Offset = Destination.GetCenter() - Source.GetCenter();
	for (const FOverlapResult& Result : OverlapResults)
	{
		if (AActor* OverlappedActor = Result.GetActor())
		{
			FVector NewLocation = OverlappedActor->GetActorLocation() + Offset;
			OverlappedActor->SetActorLocation(NewLocation);
		}
	}
}

const FBox* UToroidalSpaceComponent_Deprecated::FindBoxInsideBound(const TArray<FBox>& Boxes, const FBox& Bound) const
{
	if (Boxes.Num() == 0)
	{
		UE_LOG(LogMyVamSur, Warning, TEXT("Boxes is empty"));
		return nullptr;
	}

	for (const FBox& Box : Boxes)
	{
		if (Bound.IsInsideXY(Box.GetCenter()))
		{
			return &Box;
		}
	}

	return nullptr;
}
