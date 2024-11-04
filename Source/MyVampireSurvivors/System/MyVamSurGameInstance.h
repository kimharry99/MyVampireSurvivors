// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "MyVamSurGameInstance.generated.h"

class UDataTable;

USTRUCT(BlueprintType)
struct MYVAMPIRESURVIVORS_API FLevelExpData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FLevelExpData()
	: Level(1)
	, MaxExp(10)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 MaxExp;
};

UCLASS()
class MYVAMPIRESURVIVORS_API UMyVamSurGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	FLevelExpData* GetLevelExpData(int32 Level);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Data")
	TObjectPtr<UDataTable> ExpDataTable;
};
