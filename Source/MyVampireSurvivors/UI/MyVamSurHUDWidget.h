// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyVamSurHUDWidget.generated.h"

class AGameStateBase;
class APlayerState;
class UProgressBar;
class UTextBlock;

class AMyVamSurGameState;
class AMyVamSurPlayerState;

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
	void BindPlayerState(APlayerState* PlayerState);

private:
	UPROPERTY()
	TObjectPtr<UTextBlock> TextTime;

	UPROPERTY()
	TObjectPtr<UProgressBar> PBExp;

	UPROPERTY()
	TObjectPtr<AMyVamSurGameState> MyVamSurGameState;

	UPROPERTY()
	TObjectPtr<AMyVamSurPlayerState> MyVamSurPlayerState;

private:
	UFUNCTION()
	void UpdateTextTime(double NewGameTime);

	UFUNCTION()
	void UpdateExpBar();

	void UnInitializeGameStateDelegates();
	void UnInitializePlayerStateDelegates();
};
