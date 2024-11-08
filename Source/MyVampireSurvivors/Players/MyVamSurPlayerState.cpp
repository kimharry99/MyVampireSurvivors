// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/MyVamSurPlayerState.h"

#include "Characters/HealthData.h"
#include "Players/ExpData.h"

AMyVamSurPlayerState::AMyVamSurPlayerState()
{
}

void AMyVamSurPlayerState::BeginPlay()
{
	Super::BeginPlay();
}

void AMyVamSurPlayerState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UnInitializeExpDataDelegates();

	Super::EndPlay(EndPlayReason);
}

void AMyVamSurPlayerState::HandlePlayerStateChanged()
{
	OnPlayerStateChanged.Broadcast();
}

void AMyVamSurPlayerState::UnInitializeExpDataDelegates()
{
	if (ExpData)
	{
		ExpData->OnExpChanged.RemoveAll(this);
		ExpData->OnLevelUp.RemoveAll(this);
	}
}

void AMyVamSurPlayerState::BindHealthData(const UHealthData* NewHealthData)
{
	HealthData = NewHealthData;

	// Add HandlePlayerStateChanged to HealthData's OnHealthChanged delegate
}

void AMyVamSurPlayerState::UnBindHealthData()
{
	BindHealthData(nullptr);
}

float AMyVamSurPlayerState::GetHpRatio() const
{
	if (HealthData == nullptr)
	{
		return 0.0f;
	}

	return HealthData->GetHpRatio();
}

void AMyVamSurPlayerState::BindExpData(const UExpData* NewExpData)
{
	UnInitializeExpDataDelegates();
	ExpData = NewExpData;

	if (ExpData)
	{
		ExpData->OnExpChanged.AddDynamic(this, &AMyVamSurPlayerState::HandlePlayerStateChanged);
		ExpData->OnLevelUp.AddDynamic(this, &AMyVamSurPlayerState::HandlePlayerStateChanged);
		ExpData->OnLevelUp.AddDynamic(this, &AMyVamSurPlayerState::HandleCharacterLevelUp);
	}
}

void AMyVamSurPlayerState::UnBindExpData()
{
	BindExpData(nullptr);
}

float AMyVamSurPlayerState::GetExpRatio() const
{
	if (ExpData)
	{
		return ExpData->GetExpRatio();
	}

	return 0.0f;
}

void AMyVamSurPlayerState::HandleCharacterLevelUp()
{
	OnCharacterLevelUp.Broadcast();
}
