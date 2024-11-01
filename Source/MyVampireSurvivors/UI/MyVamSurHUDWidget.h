// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyVamSurHUDWidget.generated.h"

class AGameStateBase;
class UTextBlock;

class AMyVamSurGameState;

/**
 * 
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UMyVamSurHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	//~UUserWidget interface
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	//~End of UUserWidget interface

public:
	void BindGameState(AGameStateBase* GameState);

private:
	UPROPERTY()
	TObjectPtr<UTextBlock> TextTime;

	UPROPERTY()
	TObjectPtr<AMyVamSurGameState> MyVamSurGameState;

private:
	UFUNCTION()
	void UpdateTextTime(double NewGameTime);
};
