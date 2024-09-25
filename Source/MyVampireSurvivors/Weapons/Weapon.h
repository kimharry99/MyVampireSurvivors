// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Characters/MyVamSurCharacter.h"
#include "Enemies/Enemy.h"
#include "Weapon.generated.h"

/**
 * Base class for weapons.
 */
UCLASS(Abstract)
class MYVAMPIRESURVIVORS_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	//~AActor interface
	virtual void BeginPlay() override;
	//~End of AActor interface

	/**
	 * Use the weapon.
	 */
	virtual void UseWeapon();

	/**
	 * Attack an enemy.
	 *
	 * @param Enemy The enemy to attack.
	 */
	virtual void AttackEnemy(AEnemy* Enemy);

private:
	/**
	 * The damage dealt by the weapon.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float Damage = 0.0f;
};
