// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EquipmentAbilityNodeDefinition.generated.h"

class UPaperSprite;

UCLASS(ClassGroup = Equipment, Const, Abstract)
class MYVAMPIRESURVIVORS_API UEquipmentAbilityNodeDefinition : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditInstanceOnly, Category = "Node Information")
	FText Name = FText::FromString(TEXT(""));

	UPROPERTY(EditInstanceOnly, Category = "Node Information")
	FText Description = FText::FromString(TEXT(""));

	UPROPERTY(EditInstanceOnly, Category = "Node Information")
	TObjectPtr<UPaperSprite> Icon = nullptr;

private:
	UPROPERTY(EditInstanceOnly, Category = "Ability Tree")
	TArray<TObjectPtr<const UEquipmentAbilityNodeDefinition>> ChildNodes;

public:
	TArray<const UEquipmentAbilityNodeDefinition*> GetChildren() const;
};
