// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Equipment.generated.h"

/**
 * Base class for equipments.
 */
UCLASS(Abstract)
class MYVAMPIRESURVIVORS_API AEquipment : public AActor
{
	GENERATED_BODY()
	
public:	
	AEquipment();

public:
	/**
	 * Returns true, if the equipment can be used.
	 */
	virtual bool IsUsable() const;

	/**
	 * Use the equipment.
	 */
	virtual void UseEquipment();

protected:
	//~AActor interface
	virtual void BeginPlay() override;
	//~End of AActor interface
};
