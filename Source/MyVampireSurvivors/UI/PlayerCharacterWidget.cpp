// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerCharacterWidget.h"

#include "Components/ProgressBar.h"

#include "Characters/HealthComponent.h"

void UPlayerCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HealthBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	check(HealthBar);

	UpdateHealth();
}

void UPlayerCharacterWidget::NativeDestruct()
{	
	if (TrackingHealthComponent.IsValid())
	{
		TrackingHealthComponent->OnHealthChanged.RemoveAll(this);
	}

	Super::NativeDestruct();
}

void UPlayerCharacterWidget::BindHealthComponent(UHealthComponent* NewHealthComponent)
{
	if (TrackingHealthComponent == NewHealthComponent)
	{
		return;
	}

	if (TrackingHealthComponent.IsValid())
	{
		TrackingHealthComponent->OnHealthChanged.RemoveAll(this);
	}

	TrackingHealthComponent = NewHealthComponent;
	UpdateHealth();

	if (TrackingHealthComponent.IsValid())
	{
		TrackingHealthComponent->OnHealthChanged.AddDynamic(this, &UPlayerCharacterWidget::UpdateHealth);
	}
}

void UPlayerCharacterWidget::UpdateHealth()
{
	if (TrackingHealthComponent.IsValid())
	{
		HealthBar->SetPercent(TrackingHealthComponent->GetHPRatio());
	}
}
