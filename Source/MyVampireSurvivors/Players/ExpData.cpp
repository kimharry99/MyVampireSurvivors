// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/ExpData.h"

#include "System/MyVamSurGameInstance.h"
#include "MyVamSurLogChannels.h"

UExpData::UExpData(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CurrentExp = 0;
	CurrentLevel = 1;
}

void UExpData::AddExp(int GainedExp)
{
	CurrentExp += GainedExp;
	OnExpChanged.Broadcast();

	if (CurrentExp >= CurrentMaxExp)
	{
		LevelUp();
	}
}

void UExpData::InitializeExp()
{
	UpdateMaxExp();
	OnExpChanged.Broadcast();
}

void UExpData::LevelUp()
{
	CurrentLevel++;
	const int RemainExp = CurrentExp - CurrentMaxExp;
	UE_CLOG(RemainExp < 0, LogMyVamSur, Error, TEXT("RemainExp is less than 0."));
	UpdateMaxExp();
	OnLevelUp.Broadcast();

	CurrentExp = 0;
	AddExp(RemainExp);
}

float UExpData::GetExpRatio() const
{
	return (float)CurrentExp / (float)CurrentMaxExp;
}

int UExpData::GetMaxExp() const
{
	return CurrentMaxExp;
}

void UExpData::UpdateMaxExp()
{
	if (UWorld* World = GetWorld())
	{
		if (UMyVamSurGameInstance* GameInstance = World->GetGameInstance<UMyVamSurGameInstance>())
		{
			if (FLevelExpData* LevelData = GameInstance->GetLevelExpData(CurrentLevel))
			{
				CurrentMaxExp = LevelData->MaxExp;
			}
		}
	}
}
