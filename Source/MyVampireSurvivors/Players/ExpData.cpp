// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/ExpData.h"
#include "MyVamSurLogChannels.h"

void UExpData::AddExp(int GainedExp)
{
	CurrentExp += GainedExp;
	OnExpChanged.Broadcast();
}

float UExpData::GetExpRatio() const
{
	return (float)CurrentExp / (float)MaxExp;
}
