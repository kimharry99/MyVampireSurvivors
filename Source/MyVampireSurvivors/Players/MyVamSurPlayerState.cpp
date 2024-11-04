// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/MyVamSurPlayerState.h"

#include "Characters/HealthData.h"
#include "Players/ExpData.h"

AMyVamSurPlayerState::AMyVamSurPlayerState()
{
	ExpData = CreateDefaultSubobject<UExpData>(TEXT("ExpData"));
	check(ExpData);
}

void AMyVamSurPlayerState::BeginPlay()
{
	Super::BeginPlay();

	ExpData->Initialize();
}

void AMyVamSurPlayerState::BindHealthData(const UHealthData* NewHealthData)
{
	HealthData = NewHealthData;
}

float AMyVamSurPlayerState::GetHpRatio() const
{
	if (HealthData == nullptr)
	{
		return 0.0f;
	}

	return HealthData->GetHpRatio();
}

UExpData* AMyVamSurPlayerState::GetExpData() const
{
	return ExpData;
}
