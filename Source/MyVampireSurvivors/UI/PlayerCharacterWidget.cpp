// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerCharacterWidget.h"

#include "Components/ProgressBar.h"

#include "Characters/HealthData.h"
#include "MyVamSurLogChannels.h"

void UPlayerCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HealthBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
	check(HealthBar);

	UpdateHealth();
}

void UPlayerCharacterWidget::NativeDestruct()
{
	Super::NativeDestruct();
	
	if (TrackingHealthData)
	{
		TrackingHealthData->OnHealthChanged.RemoveAll(this);
	}
}

void UPlayerCharacterWidget::BindHealthData(UHealthData* NewHealthData)
{
	if (TrackingHealthData)
	{
		TrackingHealthData->OnHealthChanged.RemoveAll(this);
	}

	TrackingHealthData = NewHealthData;
	UpdateHealth();

	TrackingHealthData->OnHealthChanged.AddDynamic(this, &UPlayerCharacterWidget::UpdateHealth);
}

void UPlayerCharacterWidget::UpdateHealth()
{
	if (TrackingHealthData == nullptr)
	{
		return;
	}

	if (HealthBar == nullptr)
	{
		return;
	}

	UE_LOG(LogMyVamSur, Log, TEXT("UpdateHealth: %f"), TrackingHealthData->GetHpRatio());
	HealthBar->SetPercent(TrackingHealthData->GetHpRatio());
}
