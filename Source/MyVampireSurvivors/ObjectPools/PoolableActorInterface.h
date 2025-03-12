// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PoolableActorInterface.generated.h"

class IPoolableActorInterface;

DECLARE_DELEGATE_OneParam(FReturnToPoolDelegate, IPoolableActorInterface*);

UINTERFACE(MinimalAPI)
class UPoolableActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class MYVAMPIRESURVIVORS_API IPoolableActorInterface
{
	GENERATED_BODY()

public:
	virtual void ActivateFromPool() = 0;

	virtual void DeactivateToPool() = 0;

	virtual FReturnToPoolDelegate* GetReturnToPoolDelegate() = 0;

	virtual bool IsInUse() const = 0;
};
