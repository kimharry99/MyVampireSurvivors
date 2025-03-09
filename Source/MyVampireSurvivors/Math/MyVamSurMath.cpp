// Fill out your copyright notice in the Description page of Project Settings.


#include "Math/MyVamSurMath.h"

double FMyVamSurMath::GetValueCycledToRange(double Value, double RangeMin, double RangeSize)
{
	double WrappedValue = FMath::Fmod(Value - RangeMin, RangeSize) + RangeMin;
	if (WrappedValue < RangeMin)
	{
		WrappedValue += RangeSize;
	}
	return WrappedValue;
}
