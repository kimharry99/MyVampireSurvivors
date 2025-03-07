// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentAnimationData.generated.h"

class UPaperFlipbook;

/**
 *
 */
USTRUCT(BlueprintType)
struct MYVAMPIRESURVIVORS_API FEquipmentAnimationData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UPaperFlipbook> Flipbook = nullptr;

	UPROPERTY(EditAnywhere)
	FVector FlipbookOffset = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
	int NotifyKeyFrame = 0;

public:
	friend bool operator==(const FEquipmentAnimationData& Lhs, const FEquipmentAnimationData& Rhs);

	void Reset();
};
