// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MyVamSurMenuWidget.h"

#include "GameFramework/PlayerController.h"

#include "Players/PlayerCharacter.h"

void UMyVamSurMenuWidget::ExecuteOptionSelectedCallBack(const FOnMenuOptionSelected& CallBack, int SelectedOption)
{
	CallBack.ExecuteIfBound(SelectedOption);
}

int UMyVamSurMenuWidget::GetOptionCount() const
{
	return 3.0;
}
