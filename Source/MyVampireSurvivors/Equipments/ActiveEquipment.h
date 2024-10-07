// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipments/Equipment.h"
#include "ActiveEquipment.generated.h"

/**
 * The equipment which has cooldown.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API AActiveEquipment : public AEquipment
{
	GENERATED_BODY()

public:
	AActiveEquipment();

protected:
	//~AActor interface
	virtual void Tick(float DeltaTime) override;
	//~End of AActor interface

public:
	//~AEquipment interface
	virtual bool IsUsable() const override;
	virtual void UseEquipment() override;
	//~End of AEquipment interface

protected:
	/**
	 * Returns the cooldown of the equipment.
	 */
	float GetCoolDown() const;

private:
	/** Cooldown(sec) of the equipment. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Equipment|Active")
	float CoolDown = 0.0f;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Equipment|Active")
	float RemainCoolDown = 0.0f;
};
