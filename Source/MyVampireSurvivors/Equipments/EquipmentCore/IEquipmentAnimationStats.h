// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IEquipmentAnimationStats.generated.h"

struct FEquipmentAnimationData;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAnimationChanged, const FEquipmentAnimationData&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnAnimationSizeChanged, const float);

UINTERFACE(MinimalAPI)
class UEquipmentAnimationStats : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MYVAMPIRESURVIVORS_API IEquipmentAnimationStats
{
	GENERATED_BODY()

public:
	virtual FEquipmentAnimationData GetAnimationData() const = 0;
	virtual void SetAnimationData(const FEquipmentAnimationData& NewAnimationData) = 0;

	virtual void AddAnimationChangeEventListener(const FOnAnimationChanged::FDelegate& Listener) = 0;
	virtual void AddAnimationSizeChangeEventListener(const FOnAnimationSizeChanged::FDelegate& Listener) = 0;
};
