// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "Equipments/ActiveEquipmentItem.h"
#include "WeaponInterface.h"
#include "AoEWeapon.generated.h"

/**
 * Attack all enemies in a box-shaped area
 */
UCLASS()
class MYVAMPIRESURVIVORS_API AAoEWeapon : public AActiveEquipmentItem, public IWeaponInterface
{
	GENERATED_BODY()

public:
	AAoEWeapon();

protected:
	/**
	 * Root component of the weapon.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> PlayerPosition;

	/**
	 * The box component that represents the attack range of the weapon.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|AoE")
	TObjectPtr<UBoxComponent> HitboxComponent;

	/**
	 * The flipbook component that represents the weapon effect.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|AoE")
	TObjectPtr<UPaperFlipbookComponent> WeaponEffectComponent;

protected:
	//~AActor interface
	virtual void BeginPlay() override;
	//~End of AActor interface

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

	/**
	 * Perform the area of effect attack.
	 */
	UFUNCTION(BlueprintCallable, Category = "Weapon|AoE", meta = (AllowPrivateAccess = "true"))
	void PerformAoEAttack();

	/**
	 * Perform the weapon trace to find all enemies in the attack range.
	 * 
	 * @param OutOverlaps The array of overlap results.
	 */
	void DoAoEWeaponTrace(TArray<FOverlapResult>& OutOverlaps);

	/**
	 * Attack all enemies in the attack range.
	 * 
	 * @param Overlaps The array of overlap results.
	 */
	void AttackHitEnemies(const TArray<FOverlapResult>& Overlaps);

	/**
	 * Play the weapon effect.
	 */
	void PlayWeaponEffect();

	/**
	 * Stop the weapon effect.
	 */
	void StopWeaponEffect();
};
