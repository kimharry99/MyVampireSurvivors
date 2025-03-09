// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ToroidalActorComponent.generated.h"

class UToroidalWorldSystem;

/**
 * Component for actors in a toroidal map.
 * Can handle the actor position.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UToroidalActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UToroidalActorComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	//~UActorComponent interface
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//~End of UActorComponent interface

private:
	TWeakObjectPtr<UToroidalWorldSystem> ToroidalWorldSystem;
};
