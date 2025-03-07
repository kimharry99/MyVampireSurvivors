// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Equipments/EquipmentCore/EquipmentAnimationData.h"
#include "Equipments/EquipmentCore/IEquipmentAnimationStats.h"
#include "Equipments/EquipmentCore/StatComponent.h"
#include "IMeleeWeaponStats.h"
#include "MeleeWeaponStatComponent.generated.h"

struct FEquipmentAnimationData;

/**
 * 
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UMeleeWeaponStatComponent : public UStatComponent, public IEquipmentAnimationStats, public IMeleeWeaponStats
{
	GENERATED_BODY()
	
public:
	UMeleeWeaponStatComponent();

public:
	//~IMeleeWeaponStats interface
	virtual int GetDamage() const override;
	virtual void AddDamage(int Value) override;
	virtual void AddDamageMultiplier(float Value) override;

	virtual float GetCooldown() const override;
	virtual void AddAttackSpeed(float Value) override;
	virtual void AddAttackSpeedMultiplier(float Value) override;

	virtual FVector GetHitboxExtent() const override;
	virtual FVector GetHitboxOffset() const override;
	virtual void AddAttackRangeMultiplier(float Value) override;
	//~End of IMeleeWeaponStats interface

	//~IEquipmentAnimationStats interface
	virtual FEquipmentAnimationData GetAnimationData() const override;
	virtual void SetAnimationData(const FEquipmentAnimationData& NewAnimationData) override;
	virtual void AddAnimationChangeEventListener(const FOnAnimationChanged::FDelegate& Listener) override;
	virtual void AddAnimationSizeChangeEventListener(const FOnAnimationSizeChanged::FDelegate& Listener) override;
	//~End of IEquipmentAnimationStats interface

	//~UStatComponent
	virtual void Reset() override;
	//~End of UStatComponent

private:
	UPROPERTY(Category = Equipment, VisibleAnywhere, Transient)
	int Damage = 0;
	UPROPERTY(Category = Equipment, VisibleAnywhere, Transient)
	float DamageMultiplier = 0.0f;

	UPROPERTY(Category = Equipment, VisibleAnywhere, Transient)
	float AttackSpeed = 0.0f;
	UPROPERTY(Category = Equipment, VisibleAnywhere, Transient)
	float AttackSpeedMultiplier = 0.0f;
	
	UPROPERTY(Category = Equipment, VisibleAnywhere, Transient)
	float HitboxMultiplier = 0.0f;

	UPROPERTY(Category = Equipment, VisibleAnywhere, Transient)
	FEquipmentAnimationData EquipmentAnimationData;

	FOnAnimationChanged OnAnimationChanged;
	FOnAnimationSizeChanged OnAnimationSizeChanged;
};
