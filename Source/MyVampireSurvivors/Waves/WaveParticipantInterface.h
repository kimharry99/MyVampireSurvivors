// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WaveParticipantInterface.generated.h"

class IWaveParticipantInterface;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnWaveActorDestroyedDelegate, IWaveParticipantInterface*);

UINTERFACE(MinimalAPI)
class UWaveParticipantInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MYVAMPIRESURVIVORS_API IWaveParticipantInterface
{
	GENERATED_BODY()

public:
	virtual FOnWaveActorDestroyedDelegate* GetOnWaveActorDestroyedDelegate() { return nullptr; }
};
