// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyVamSurPlayerController.generated.h"

template <class TClass> class TSubclassOf;
class UMyVamSurHUDWidget;

/**
 * 
 */
UCLASS()
class MYVAMPIRESURVIVORS_API AMyVamSurPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	//~AActor interface
	virtual void BeginPlay() override;
	//~End of AActor interface

	//~APlayerController interface
	virtual void OnPossess(APawn* InPawn) override;
	virtual void PlayerTick(float DeltaSeconds) override;
	//~End of APlayerController interface

private:
	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<UMyVamSurHUDWidget> HUDWidgetClass;

	UPROPERTY()
	TObjectPtr<UMyVamSurHUDWidget> HUDWidget;

private:
	void CreateHUDWidget();
};
