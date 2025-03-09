// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
struct MYVAMPIRESURVIVORS_API FMyVamSurMath
{
public:
	template <typename T>
	static T GetClosestValue(const T Target, const T A, const T B)
	{
		return (FMath::Abs(Target - A) < FMath::Abs(Target - B)) ? A : B;
	}

	template <typename T>
	static TArray<UE::Math::TBox2<T>> DivideBox2D(const UE::Math::TBox2<T>& Box, const TArray<T>& VerticalLines, const TArray<T>& HorizontalLines)
	{
		TArray<UE::Math::TBox2<T>> SubBoxes;

		TArray<T> FilteredX;
		FilteredX.Add(Box.Min.X);
		FilteredX.Add(Box.Max.X);
		for (const auto& X : VerticalLines)
		{
			if (Box.Min.X < X && X < Box.Max.X)
			{
				FilteredX.Add(X);
			}
		}
		FilteredX.Sort();

		TArray<T> FilteredY;
		FilteredY.Add(Box.Min.Y);
		FilteredY.Add(Box.Max.Y);
		for (const auto& Y : HorizontalLines)
		{
			if (Box.Min.Y < Y && Y < Box.Max.Y)
			{
				FilteredY.Add(Y);
			}
		}
		FilteredY.Sort();

		for (int i = 0; i < FilteredX.Num() - 1; ++i)
		{
			for (int j = 0; j < FilteredY.Num() - 1; ++j)
			{
				UE::Math::TVector2<T> Min(FilteredX[i], FilteredY[j]);
				UE::Math::TVector2<T> Max(FilteredX[i + 1], FilteredY[j + 1]);

				SubBoxes.Add(UE::Math::TBox2<T>(Min, Max));
			}
		}

		return SubBoxes;
	}

	/**
	 * Divides the given Box into smaller boxes using the edges of Bounds.
	 */
	template <typename T>
	static TArray<UE::Math::TBox2<T>> DivideBox2D(const UE::Math::TBox2<T>& Box, const UE::Math::TBox<T>& Bounds)
	{
		TArray<T> VerticalLines;
		VerticalLines.Add(Bounds.Min.X);
		VerticalLines.Add(Bounds.Max.X);

		TArray<T> HorizontalLines;
		HorizontalLines.Add(Bounds.Min.Y);
		HorizontalLines.Add(Bounds.Max.Y);

		return FMyVamSurMath::DivideBox2D(Box, VerticalLines, HorizontalLines);
	}

	template <typename T>
	static FIntVector2 GetDirectionVector(const UE::Math::TVector2<T>& From, const UE::Math::TVector2<T>& To)
	{
		UE::Math::TVector2<T> Direction = To - From;
		return FIntVector2(
			FMath::IsNearlyZero(Direction.X) ? 0 : static_cast<int>(FMath::Sign(Direction.X)),
			FMath::IsNearlyZero(Direction.Y) ? 0 : static_cast<int>(FMath::Sign(Direction.Y))
		);
	}

	static double GetValueCycledToRange(double Value, double RangeMin, double RangeSize);

	template <typename T>
	static T GetCircularDistance(T From, T To, T RangeSize)
	{
		T Distance = FMath::Abs(To - From);
		return FMath::Min(Distance, RangeSize - Distance);
	}

	template <typename T>
	static T GetSignedCircularDistance(T From, T To, T RangeSize)
	{
		const T Displacement = To - From;
		const T Sign = FMath::Abs(Displacement) <= RangeSize / 2.0 ? FMath::Sign(Displacement) : -FMath::Sign(Displacement);

		const T Distance = FMyVamSurMath::GetCircularDistance(From, To, RangeSize);
		return Sign * Distance;
	}
};


