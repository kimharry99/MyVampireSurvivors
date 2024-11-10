// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EquipmentDefinition.generated.h"

template <class TClass> class TSubclassOf;
class UPaperSprite;

class AEquipmentItem;

UCLASS(Blueprintable, Const)
class MYVAMPIRESURVIVORS_API UEquipmentDefinition : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UPaperSprite> Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AEquipmentItem> EquipmentClass;
};
