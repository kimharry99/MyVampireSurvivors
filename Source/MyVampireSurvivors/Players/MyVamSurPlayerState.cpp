// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/MyVamSurPlayerState.h"

#include "Characters/HealthData.h"
#include "Players/ExpData.h"

AMyVamSurPlayerState::AMyVamSurPlayerState()
{
	HealthData = CreateDefaultSubobject<UHealthData>(TEXT("HealthData"));
	check(HealthData);

	ExpData = CreateDefaultSubobject<UExpData>(TEXT("ExpData"));
	check(ExpData);
}

void AMyVamSurPlayerState::BeginPlay()
{
	Super::BeginPlay();

	ExpData->Initialize();
}

UHealthData* AMyVamSurPlayerState::GetHealthData() const
{
	return HealthData;
}

UExpData* AMyVamSurPlayerState::GetExpData() const
{
	return ExpData;
}
