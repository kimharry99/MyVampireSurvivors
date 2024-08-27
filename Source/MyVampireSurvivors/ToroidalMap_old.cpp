// Fill out your copyright notice in the Description page of Project Settings.


#include "ToroidalMap_old.h"

ToroidalMap_old::ToroidalMap_old(float InWidth, float InHeight): Width(InHeight), Height(InHeight)
{
}

FVector ToroidalMap_old::WrapPosition(const FVector& Position) const
{
    FVector NewPosition = Position;

    if (NewPosition.X < 0)
    {
        NewPosition.X += Width;
    }
    else if (NewPosition.X > Width)
    {
        NewPosition.X -= Width;
    }

    if (NewPosition.Y < 0)
    {
        NewPosition.Y += Height;
    }
    else if (NewPosition.Y > Height)
    {
        NewPosition.Y -= Height;
    }

    return NewPosition;
}
