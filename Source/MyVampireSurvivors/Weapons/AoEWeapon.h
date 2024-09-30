// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Equipments/ActiveEquipment.h"
#include "WeaponInterface.h"
#include "AoEWeapon.generated.h"

/**
 * Attack all enemies in a box-shaped area
 */
UCLASS()
class MYVAMPIRESURVIVORS_API AAoEWeapon : public AActiveEquipment, public IWeaponInterface
{
	GENERATED_BODY()

public:
	AAoEWeapon();

protected:
	/**
	 * The box component that represents the attack range of the weapon.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|AoE")
	TObjectPtr<UBoxComponent> AttackRangeComponent;

protected:
	//~IWeaponInterface interface
	virtual AController* GetController() const override;
	virtual float GetWeaponDamage() const override;
	//~End of IWeaponInterface interface

	//~AEquipment interface
	virtual void UseEquipment() override;
	//~End of AEquipment interface

private:
	/**
	 * The damage dealt by the weapon.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Weapon")
	float Damage = 0.0f;
};
