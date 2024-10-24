// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/MyVamSurPlayerState.h"
#include "Players/HealthData.h"

AMyVamSurPlayerState::AMyVamSurPlayerState()
{
	HealthData = CreateDefaultSubobject<UHealthData>(TEXT("HealthData"));
}

UHealthData* AMyVamSurPlayerState::GetHealthData() const
{
	return HealthData;
}
