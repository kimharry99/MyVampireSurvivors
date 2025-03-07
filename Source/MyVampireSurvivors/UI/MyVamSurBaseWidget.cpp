// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MyVamSurBaseWidget.h"

#include "Widgets/CommonActivatableWidgetContainer.h"

#include "UI/MyVamSurMenuWidget.h"
#include "UI/MyVamSurHUDWidget.h"

void UMyVamSurBaseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HUD = Cast<UMyVamSurHUDWidget>(GetWidgetFromName(TEXT("HUD")));
	check(HUD);

	MenuStack = Cast<UCommonActivatableWidgetStack>(GetWidgetFromName(TEXT("MenuStack")));
	check(MenuStack);
}

UMyVamSurMenuWidget* UMyVamSurBaseWidget::PushMenu(TSubclassOf<UMyVamSurMenuWidget> MenuWidgetClass)
{
	if (MenuStack)
	{
		UMyVamSurMenuWidget* Widget = Cast<UMyVamSurMenuWidget>(MenuStack->AddWidget(MenuWidgetClass));
		return Widget;
	}

	return nullptr;
}
