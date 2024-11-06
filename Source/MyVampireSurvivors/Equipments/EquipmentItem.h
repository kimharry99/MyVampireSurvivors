// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "EquipmentItem.generated.h"


USTRUCT(BlueprintType)
struct MYVAMPIRESURVIVORS_API FEquipmentStat : public FTableRowBase
{
	GENERATED_BODY()

	FEquipmentStat()
	: Level(1)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int Level;

	static const FName MaxLevelRowName;
};


/**
 * Base class for equipments.
 */
UCLASS(Abstract)
class MYVAMPIRESURVIVORS_API AEquipmentItem : public AActor
{
	GENERATED_BODY()
	
public:
	AEquipmentItem();

protected:
	//~AActor interface
	virtual void BeginPlay() override;
	//~End of AActor interface

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
	UPROPERTY(Transient, VisibleAnywhere, Category = "Equipment")
	int EquipmentLevel = 1;

	UPROPERTY(Transient, VisibleAnywhere, Category = "Equipment")
	int MaxEquipmentLevel = 999;

public:
	bool CanUpgrade() const;
	int GetEquipmentLevel() const;

	virtual void Upgrade();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	TObjectPtr<UDataTable> EquipmentStatTable;

protected:
	virtual void SetEquipmentStat(int Level);

	virtual void InitializeLevel();
};
