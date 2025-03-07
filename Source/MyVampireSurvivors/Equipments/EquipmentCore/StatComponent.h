// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatComponent.generated.h"


UCLASS(ClassGroup = "Equipment", Abstract)
class MYVAMPIRESURVIVORS_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UStatComponent();

public:
	virtual void Reset();
};
