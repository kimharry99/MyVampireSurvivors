// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ToroidCharacterMovementComponent.generated.h"

class UToroidalWorldSystem;

/**
 * 
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UToroidCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	bool bIsPlayingCharacter = false;

	//~UActorComponent interface
	virtual void BeginPlay() override;
	//~End of UActorComponent interface

protected:
	//~UMovementComponent interface
	virtual void OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity) override;
	//~End of UMovementComponent interface

private:
	TWeakObjectPtr<UToroidalWorldSystem> ToroidalWorldSystem;
};
