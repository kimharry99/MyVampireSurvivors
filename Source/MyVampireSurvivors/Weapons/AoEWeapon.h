// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Weapons/ActiveWeapon.h"
#include "AoEWeapon.generated.h"

/**
 * Attack all enemies in a box-shaped area
 */
UCLASS()
class MYVAMPIRESURVIVORS_API AAoEWeapon : public AActiveWeapon
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
	//~AWeapon interface
	virtual void UseWeapon();
	//~End of AWeapon interface
};
