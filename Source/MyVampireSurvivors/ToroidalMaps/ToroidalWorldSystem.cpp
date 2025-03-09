// Fill out your copyright notice in the Description page of Project Settings.


#include "ToroidalMaps/ToroidalWorldSystem.h"

#include "Math/MyMath.h"
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
	const double NewPositionX = WrapValue(Position.X, MapRange.Min.X, Width);
	const double NewPositionY = WrapValue(Position.Y, MapRange.Min.Y, Height);
	const double NewPositionZ = Position.Z;

	return FVector(NewPositionX, NewPositionY, NewPositionZ);
}

bool UToroidalWorldSystem::IsInsideBoxOnTorus(const FVector& Point, const FBox& Box) const
{
	// Wrap the center of the Box
	const FVector WrappedCenter = WrapPosition3D(Box.GetCenter());
	
	// Wrap the Point
	const FVector WrappedPoint = WrapPosition3D(Point);

	// Check if the Point is inside the Box on toroidal topology
	const FVector Extent = Box.GetExtent();
	const double MapWidth = ToroidalMap->GetMapRange().GetSize().X;
	const double MapHeight = ToroidalMap->GetMapRange().GetSize().Y;

	// Compare the box extent with a toroidal distance between the center and the point
	const bool bIsInsideX = CalculateDistance1D(WrappedCenter.X, WrappedPoint.X, MapWidth) <= Extent.X;
	const bool bIsInsideY = CalculateDistance1D(WrappedCenter.Y, WrappedPoint.Y, MapHeight) <= Extent.Y;
	return bIsInsideX && bIsInsideY;
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

	TArray<FBox2D> SubBoxes = FMyVamSurMath::DivideBox2D(WorldDistortionZone2D, VerticalLines, HorizontalLines);
	for (auto& SubBox : SubBoxes)
	{
		if (SubBox.IsInsideOrOn(WorldDistortionZone2D.GetCenter()))
		{
			continue;
		}

		FIntVector2 Delta = FMyVamSurMath::GetDirectionVector(SubBox.GetCenter(), TransformToTorus(SubBox.GetCenter()));
		DistortionZones.Emplace((Delta * -1), SubBox);
	}
}

FVector UToroidalWorldSystem::CalculateDisplacement(const FVector& From, const FVector& To) const
{
	const FVector WrappedFrom = WrapPosition3D(From);
	const FVector WrappedTo = WrapPosition3D(To);

	const double Width = ToroidalMap->GetMapRange().GetSize().X;
	const double Height = ToroidalMap->GetMapRange().GetSize().Y;
	const double DeltaX = CalculateSignedDistance1D(WrappedFrom.X, WrappedTo.X, Width);
	const double DeltaY = CalculateSignedDistance1D(WrappedFrom.Y, WrappedTo.Y, Height);

	return FVector(DeltaX, DeltaY, 0.0);
}

FVector UToroidalWorldSystem::RefineLocation(const FVector& Location) const
{
	FVector ToroidalLocation(TransformToTorus(Location));
	return TransformToWorld(ToroidalLocation);
}

double UToroidalWorldSystem::WrapValue(double Value, double RangeMin, double RangeSize) const
{
	double WrappedValue = FMath::Fmod(Value - RangeMin, RangeSize) + RangeMin;
	if (WrappedValue < RangeMin)
	{
		WrappedValue += RangeSize;
	}
	return WrappedValue;
}

double UToroidalWorldSystem::CalculateDistance1D(double From, double To, double RangeSize) const
{
	double Distance = FMath::Abs(To - From);
	return FMath::Min(Distance, RangeSize - Distance);
}

double UToroidalWorldSystem::CalculateSignedDistance1D(double From, double To, double RangeSize) const
{
	const double Displacement = To - From;
	const double Sign = FMath::Abs(Displacement) <= RangeSize / 2.0 ? FMath::Sign(Displacement) : -FMath::Sign(Displacement);
	
	const double Distance = CalculateDistance1D(From, To, RangeSize);
	return Sign * Distance;
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
	const double NewLocationX = WrapValue(Location.X, MapRange.Min.X, Width);
	const double NewLocationY = WrapValue(Location.Y, MapRange.Min.Y, Height);

	return FVector2D(NewLocationX, NewLocationY);
}

FVector UToroidalWorldSystem::TransformToWorld(const FVector& Location) const
{
	FVector2D LocationXY(Location.X, Location.Y);
	for (const auto& [Direction, DistortionZone] : DistortionZones)
	{
		if (DistortionZone.IsInside(LocationXY))
		{
			const FBox MapRange = ToroidalMap->GetMapRange();
			const double Width = MapRange.GetSize().X;
			const double Height = MapRange.GetSize().Y;

			LocationXY.X += static_cast<double>(Direction.X) * Width;
			LocationXY.Y += static_cast<double>(Direction.Y) * Height;
		}
	}

	return FVector(LocationXY.X, LocationXY.Y, Location.Z);
}
