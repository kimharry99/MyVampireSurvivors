// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EquipmentAutoActivator.generated.h"

class AEquipment;

UCLASS(ClassGroup = Equipment)
class MYVAMPIRESURVIVORS_API UEquipmentAutoActivator : public UObject
{
	GENERATED_BODY()

public:
	UEquipmentAutoActivator(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	void RegisterAndUseEquipment(AEquipment* Equipment) const;

private:
	void ExecuteUse(TWeakObjectPtr<AEquipment> Equipment) const;
};
