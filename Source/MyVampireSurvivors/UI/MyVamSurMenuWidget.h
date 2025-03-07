// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "MyVamSurMenuWidget.generated.h"

class APlayerCharacter;


DECLARE_DYNAMIC_DELEGATE_OneParam(FOnMenuOptionSelected, int, SelectedOption);

/**
 * 
 */
UCLASS(Abstract)
class MYVAMPIRESURVIVORS_API UMyVamSurMenuWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetOptionSelectedCallBack(const FOnMenuOptionSelected& CallBack);

	virtual int GetOptionCount() const;

private:
	UFUNCTION(BlueprintCallable)
	void ExecuteOptionSelectedCallBack(const FOnMenuOptionSelected& CallBack, int SelectedOption);
};
