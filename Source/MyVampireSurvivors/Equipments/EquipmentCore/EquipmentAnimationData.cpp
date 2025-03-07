// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentAnimationData.h"

void FEquipmentAnimationData::Reset()
{
	Flipbook = nullptr;
	FlipbookOffset = FVector::ZeroVector;
	NotifyKeyFrame = 0;
}

bool operator==(const FEquipmentAnimationData& Lhs, const FEquipmentAnimationData& Rhs)
{
	return Lhs.Flipbook == Rhs.Flipbook &&
		Lhs.FlipbookOffset == Rhs.FlipbookOffset &&
		Lhs.NotifyKeyFrame == Rhs.NotifyKeyFrame;
}
