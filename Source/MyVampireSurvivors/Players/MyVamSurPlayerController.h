// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyVamSurPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MYVAMPIRESURVIVORS_API AMyVamSurPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	//~APlayerController interface
	virtual void PlayerTick(float DeltaSeconds) override;
	//~End of APlayerController interface
};
