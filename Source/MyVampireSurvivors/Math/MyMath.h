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

		TArray<T> SortedX = VerticalLines;
		SortedX.Add(Box.Min.X);
		SortedX.Add(Box.Max.X);
		SortedX.Sort();

		TArray<T> SortedY = HorizontalLines;
		SortedY.Add(Box.Min.Y);
		SortedY.Add(Box.Max.Y);
		SortedY.Sort();

		for (int i = 0; i < SortedX.Num() - 1; ++i)
		{
			for (int j = 0; j < SortedY.Num() - 1; ++j)
			{
				UE::Math::TVector2<T> Min(SortedX[i], SortedY[j]);
				UE::Math::TVector2<T> Max(SortedX[i + 1], SortedY[j + 1]);

				SubBoxes.Add(UE::Math::TBox2<T>(Min, Max));
			}
		}

		return SubBoxes;
	}

	template <typename T>
	static FIntVector2 GetDirectionVector(const UE::Math::TVector2<T>& From, const UE::Math::TVector2<T>& To)
	{
		UE::Math::TVector2<T> Direction = To - From;
		return FIntVector2(
			FMath::Sign(static_cast<int>(Direction.X)),
			FMath::Sign(static_cast<int>(Direction.Y))
		);
	}
};
