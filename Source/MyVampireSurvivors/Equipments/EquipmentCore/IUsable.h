// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IUsable.generated.h"

UINTERFACE(MinimalAPI)
class UUsable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MYVAMPIRESURVIVORS_API IUsable
{
	GENERATED_BODY()

public:
	virtual bool IsUsable() const = 0;
	virtual void Use() = 0;
};
