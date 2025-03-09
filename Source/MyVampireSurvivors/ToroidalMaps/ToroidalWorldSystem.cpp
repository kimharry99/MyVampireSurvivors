// Fill out your copyright notice in the Description page of Project Settings.


#include "ToroidalMaps/ToroidalWorldSystem.h"

#include "Math/MyVamSurMath.h"
#include "ToroidalMaps/ToroidalMap.h"


void UToroidalWorldSystem::Initialize(AToroidalMap* LevelToroidalMap)
{
	ToroidalMap = LevelToroidalMap;
}

FVector UToroidalWorldSystem::WrapPosition3D(const FVector& Position) const
{
	FBox MapRange = ToroidalMap->GetMapRange();
	if (MapRange.IsInsideXY(Position))
	{
		return Position;
	}

	const double Width = MapRange.GetSize().X;
	const double Height = MapRange.GetSize().Y;
	const double NewPositionX = FMyVamSurMath::GetValueCycledToRange(Position.X, MapRange.Min.X, Width);
	const double NewPositionY = FMyVamSurMath::GetValueCycledToRange(Position.Y, MapRange.Min.Y, Height);
	const double NewPositionZ = Position.Z;

	return FVector(NewPositionX, NewPositionY, NewPositionZ);
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

	FBox2D WorldDistortionZone2D(
		FVector2D(WorldDistortionZone.Min.X, WorldDistortionZone.Min.Y),
		FVector2D(WorldDistortionZone.Max.X, WorldDistortionZone.Max.Y)
	);

	TArray<double> VerticalLines;
	double ClosestX = FMyVamSurMath::GetClosestValue(WorldDistortionZone2D.GetCenter().X, MapRange.Min.X, MapRange.Max.X);
	if (FMath::IsWithin(ClosestX, WorldDistortionZone2D.Min.X, WorldDistortionZone2D.Max.X))
	{
		VerticalLines.Add(ClosestX);
	}

	TArray<double> HorizontalLines;
	double ClosestY = FMyVamSurMath::GetClosestValue(WorldDistortionZone2D.GetCenter().Y, MapRange.Min.Y, MapRange.Max.Y);
	if (FMath::IsWithin(ClosestY, WorldDistortionZone2D.Min.Y, WorldDistortionZone2D.Max.Y))
	{
		HorizontalLines.Add(ClosestY);
	}

	FIntVector2 FullZoneDelta = FMyVamSurMath::GetDirectionVector(WorldDistortionZone2D.GetCenter(), TransformToTorus(WorldDistortionZone2D.GetCenter()));
	TArray<FBox2D> SubBoxes = FMyVamSurMath::DivideBox2D(WorldDistortionZone2D, VerticalLines, HorizontalLines);
	for (auto& SubBox : SubBoxes)
	{
		if (SubBox.IsInsideOrOn(WorldDistortionZone2D.GetCenter()))
		{
			continue;
		}

		FBox2D ToroidalSubBox = SubBox.MoveTo(TransformToTorus(SubBox.GetCenter()));
		FIntVector2 Delta = FMyVamSurMath::GetDirectionVector(SubBox.GetCenter(), ToroidalSubBox.GetCenter());
		DistortionZones.Emplace(FullZoneDelta - Delta, ToroidalSubBox);
	}
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

FVector UToroidalWorldSystem::CalculateDisplacement(const FVector& From, const FVector& To) const
{
	const FVector WrappedFrom = WrapPosition3D(From);
	const FVector WrappedTo = WrapPosition3D(To);

	const double Width = ToroidalMap->GetMapRange().GetSize().X;
	const double Height = ToroidalMap->GetMapRange().GetSize().Y;

	const double DeltaX = FMyVamSurMath::GetSignedCircularDistance(WrappedFrom.X, WrappedTo.X, Width);
	const double DeltaY = FMyVamSurMath::GetSignedCircularDistance(WrappedFrom.Y, WrappedTo.Y, Height);

	return FVector(DeltaX, DeltaY, 0.0);
}

FVector UToroidalWorldSystem::RefineLocation(const FVector& Location, bool bActiveDistortion) const
{
	FVector ToroidalLocation(TransformToTorus(Location));
	return TransformToWorld(ToroidalLocation, bActiveDistortion);
}

FVector UToroidalWorldSystem::TransformToTorus(const FVector& Location) const
{
	FVector2D Location2D = FVector2D(Location.X, Location.Y);
	FVector2D ToroidalLocation = TransformToTorus(Location2D);

	return FVector(ToroidalLocation.X, ToroidalLocation.Y, Location.Z);
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
