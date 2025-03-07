// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UI/IDisplableObject.h"
#include "UpgradeOption.generated.h"

class AEquipment;

/**
 *
 */
UCLASS(Abstract)
class MYVAMPIRESURVIVORS_API UUpgradeOption : public UObject, public IDisplableObject
{
	GENERATED_BODY()

protected:
	UUpgradeOption();

public:
	//~IDisplableObject interface
	virtual const FText GetObjectName() const override;
	virtual const FText GetDescription() const override;
	virtual const UPaperSprite* GetIcon() const override;
	//~End of IDisplableObject interface

public:
	virtual bool IsActive() const;
	virtual AEquipment* GetOwningEquipment() const;
};
