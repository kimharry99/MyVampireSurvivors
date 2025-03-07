// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "MyVamSurBaseWidget.generated.h"

template <class TClass> class TSubclassOf;
class UCommonActivatableWidgetStack;

class UMyVamSurHUDWidget;
class UMyVamSurMenuWidget;
class URewardMenuWidget;


/**
 * 
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UMyVamSurBaseWidget : public UCommonUserWidget
{
	GENERATED_BODY()

protected:
	//~UUserWidget interface
	virtual void NativeConstruct() override;
	//~End of UUserWidget interface

private:
	UPROPERTY()
	TObjectPtr<UMyVamSurHUDWidget> HUD;

	UPROPERTY()
	TObjectPtr<UCommonActivatableWidgetStack> MenuStack;

private:
	UFUNCTION(BlueprintCallable, Category = UI)
	UMyVamSurMenuWidget* PushMenu(TSubclassOf<UMyVamSurMenuWidget> MenuWidgetClass);

public:
	UFUNCTION(BlueprintImplementableEvent, Category = UI)
	URewardMenuWidget* DisplayLevelUpMenu();
};
