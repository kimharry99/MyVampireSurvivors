// Fill out your copyright notice in the Description page of Project Settings.


#include "System/MyVamSurGameInstance.h"

FLevelExpData* UMyVamSurGameInstance::GetLevelExpData(int32 Level)
{
	if (ExpDataTable)
	{
		return ExpDataTable->FindRow<FLevelExpData>(*FString::FromInt(Level), TEXT(""));
	}

	return nullptr;
}
