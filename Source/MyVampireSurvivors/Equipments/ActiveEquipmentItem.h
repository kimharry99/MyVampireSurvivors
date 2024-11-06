// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipments/EquipmentItem.h"
#include "ActiveEquipmentItem.generated.h"


USTRUCT(BlueprintType)
struct MYVAMPIRESURVIVORS_API FActiveEquipmentStat : public FEquipmentStat
{
	GENERATED_BODY()

	FActiveEquipmentStat()
	: CoolDown(0.1f)
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	float CoolDown;
};


/**
 * The equipment which has cooldown.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API AActiveEquipmentItem : public AEquipmentItem
{
	GENERATED_BODY()

public:
	AActiveEquipmentItem();

protected:
	//~AActor interface
	virtual void Tick(float DeltaTime) override;
	//~End of AActor interface

public:
	//~AEquipmentItem interface
	virtual bool IsUsable() const override;
	virtual void UseEquipment() override;
protected:
	virtual void SetEquipmentStat(int Level) override;
	//~End of AEquipmentItem interface

private:
	/** Cooldown(sec) of the equipment. */
	UPROPERTY(Transient, VisibleAnywhere, Category = "Equipment|Active")
	float CoolDown = 1.0f;

	UPROPERTY(Transient, VisibleAnywhere, Category = "Equipment|Active")
	float RemainCoolDown = 0.0f;

protected:
	/**
	 * Returns the cooldown of the equipment.
	 */
	float GetCoolDown() const;

private:
	void SetCoolDown(float NewCoolDown);
};
