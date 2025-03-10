// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WaveClearHandlerComponent.generated.h"

class AWave;

/**
 * WaveClearHandlerComponent is responsible for monitoring active waves, handling their completion,
 * and broadcasting an event when all waves have been cleared. It listens for wave-cleared events
 * and maintains a list of active waves to ensure proper tracking.
 */
UCLASS(ClassGroup = "Wave")
class MYVAMPIRESURVIVORS_API UWaveClearHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWaveClearHandlerComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	bool IsAnyTriggeredWaveUncleared() const;

	UFUNCTION()
	void HandleWaveTriggered(AWave* Wave);

	UFUNCTION()
	void HandleWaveClear(AWave* ClearedWave);

	FSimpleMulticastDelegate OnWaveCleared;

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	TSet<TWeakObjectPtr<AWave>> TriggeredWaves;
};
