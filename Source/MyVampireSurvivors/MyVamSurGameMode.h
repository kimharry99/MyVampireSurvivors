// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyVamSurGameMode.generated.h"

class UToroidalWorldSystem;

/**
 * 
 */
UCLASS()
class MYVAMPIRESURVIVORS_API AMyVamSurGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	//~AGameModeBase interface
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	//~End of AGameModeBase interface

public:
	/**
	 * Returns the toroidal world system.
	 */
	UToroidalWorldSystem* GetToroidalWorldSystem() const;

private:
	UPROPERTY()
	TObjectPtr<UToroidalWorldSystem> ToroidalWorldSystem;

	/**
	 * Add the toroidal world system to the game.
	 */
	void AddToroidalWorldSystemToGame();
};
