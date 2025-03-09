// Fill out your copyright notice in the Description page of Project Settings.


#include "ToroidalMaps/ToroidalWorldSystem.h"

#include "Math/MyVamSurMath.h"
#include "ToroidalMaps/ToroidalMap.h"


void UToroidalWorldSystem::Initialize(AToroidalMap* LevelToroidalMap)
{
	ToroidalMap = LevelToroidalMap;
}

TArray<FBox2D> UToroidalWorldSystem::GetDistortionZones() const
{
	TArray<FBox2D> Result;
	for (const auto& [_, Zone] : DistortionZones)
	{
		Result.Add(Zone);
	}

	return Result;
}

void UToroidalWorldSystem::SetDistortionZone(const FBox& WorldDistortionZone)
{
	DistortionZones.Empty();

	FBox MapRange = ToroidalMap->GetMapRange();
	// Check if there are any parts outside the map.
	if (MapRange.IsInsideXY(WorldDistortionZone))
	{
		return;
	}

	FBox ToroidalCompleteZone = WorldDistortionZone.MoveTo(TransformToTorus(WorldDistortionZone.GetCenter()));
	FBox2D ToroidalCompleteZone2D = FBox2D(
		FVector2D(ToroidalCompleteZone.Min.X, ToroidalCompleteZone.Min.Y),
		FVector2D(ToroidalCompleteZone.Max.X, ToroidalCompleteZone.Max.Y)
	);
	
	TArray<FBox2D> SubZones = FMyVamSurMath::DivideBox2D(ToroidalCompleteZone2D, MapRange);
	for (auto& SubZone : SubZones)
	{
		FBox2D ToroidalSubZone = SubZone.MoveTo(TransformToTorus(SubZone.GetCenter()));
		FIntVector2 Delta = FMyVamSurMath::GetDirectionVector(SubZone.GetCenter(), ToroidalSubZone.GetCenter());
		if (Delta.X == 0 && Delta.Y == 0)
		{
			continue;
		}

		DistortionZones.Emplace(Delta * -1, ToroidalSubZone);
	}
}

FVector UToroidalWorldSystem::CalculateDisplacement(const FVector& From, const FVector& To) const
{
	const FVector FromOnTorus = TransformToTorus(From);
	const FVector ToOnTorus = TransformToTorus(To);

	const double Width = ToroidalMap->GetMapRange().GetSize().X;
	const double Height = ToroidalMap->GetMapRange().GetSize().Y;

	const double DeltaX = FMyVamSurMath::GetSignedCircularDistance(FromOnTorus.X, ToOnTorus.X, Width);
	const double DeltaY = FMyVamSurMath::GetSignedCircularDistance(FromOnTorus.Y, ToOnTorus.Y, Height);

	return FVector(DeltaX, DeltaY, 0.0);
}

FVector UToroidalWorldSystem::RefineLocation(const FVector& Location, bool bActiveDistortion) const
{
	FVector ToroidalLocation(TransformToTorus(Location));
	return TransformToWorld(ToroidalLocation, bActiveDistortion);
}

FVector2D UToroidalWorldSystem::TransformToTorus(const FVector2D& Location) const
{
	FBox MapRange = ToroidalMap->GetMapRange();
	if (MapRange.IsInside(FVector(Location.X, Location.Y, MapRange.GetCenter().Z)))
	{
		return Location;
	}

	const double Width = MapRange.GetSize().X;
	const double Height = MapRange.GetSize().Y;
	const double NewLocationX = FMyVamSurMath::GetValueCycledToRange(Location.X, MapRange.Min.X, Width);
	const double NewLocationY = FMyVamSurMath::GetValueCycledToRange(Location.Y, MapRange.Min.Y, Height);

	return FVector2D(NewLocationX, NewLocationY);
}

FVector UToroidalWorldSystem::TransformToTorus(const FVector& Location) const
{
	FVector2D Location2D = FVector2D(Location.X, Location.Y);
	FVector2D ToroidalLocation = TransformToTorus(Location2D);

	return FVector(ToroidalLocation.X, ToroidalLocation.Y, Location.Z);
}

FVector UToroidalWorldSystem::TransformToWorld(const FVector& Location, const bool bActiveDistortion) const
{
	FVector2D LocationXY(Location.X, Location.Y);
	if (bActiveDistortion)
	{
		for (const auto& [Direction, DistortionZone] : DistortionZones)
		{
			if (DistortionZone.IsInside(LocationXY))
			{
				const FBox MapRange = ToroidalMap->GetMapRange();
				const double Width = MapRange.GetSize().X;
				const double Height = MapRange.GetSize().Y;

				LocationXY.X += static_cast<double>(Direction.X) * Width;
				LocationXY.Y += static_cast<double>(Direction.Y) * Height;

				break;
			}
		}
	}

	return FVector(LocationXY.X, LocationXY.Y, Location.Z);
}
