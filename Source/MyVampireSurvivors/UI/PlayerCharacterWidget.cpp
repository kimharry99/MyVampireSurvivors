// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerCharacterWidget.h"

#include "Components/ProgressBar.h"

#include "Characters/HealthData.h"

void UPlayerCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HealthBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	check(HealthBar);

	UpdateHealth();
}

void UPlayerCharacterWidget::NativeDestruct()
{	
	if (TrackingHealthData.IsValid())
	{
		TrackingHealthData->OnHealthChanged.RemoveAll(this);
	}

	Super::NativeDestruct();
}

void UPlayerCharacterWidget::BindHealthData(UHealthData* NewHealthData)
{
	if (TrackingHealthData == NewHealthData)
	{
		return;
	}

	if (TrackingHealthData.IsValid())
	{
		TrackingHealthData->OnHealthChanged.RemoveAll(this);
	}

	TrackingHealthData = NewHealthData;
	UpdateHealth();

	if (TrackingHealthData.IsValid())
	{
		TrackingHealthData->OnHealthChanged.AddDynamic(this, &UPlayerCharacterWidget::UpdateHealth);
	}
}

void UPlayerCharacterWidget::UpdateHealth()
{
	if (TrackingHealthData.IsValid())
	{
		HealthBar->SetPercent(TrackingHealthData->GetHpRatio());
	}
}
