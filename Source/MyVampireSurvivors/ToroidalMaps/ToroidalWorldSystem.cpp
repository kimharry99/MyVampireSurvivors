// Fill out your copyright notice in the Description page of Project Settings.


#include "ToroidalMaps/ToroidalWorldSystem.h"
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
