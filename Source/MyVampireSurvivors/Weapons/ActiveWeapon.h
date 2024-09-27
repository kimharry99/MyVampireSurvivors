// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Weapon.h"
#include "ActiveWeapon.generated.h"

/**
 * Active weapon that has attack cooldown.
 */
UCLASS(Abstract)
class MYVAMPIRESURVIVORS_API AActiveWeapon : public AWeapon
{
	GENERATED_BODY()

protected:
	//~AActor interface
	virtual void Tick(float DeltaTime) override;
	//~End of AActor interface

public:
	//~AWeapon interface
	virtual bool IsUsable() const override;
	virtual void UseWeapon() override;
	//~End of AWeapon interface

private:
	/** Cooldown(sec) of the weapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Weapon")
	float CoolDown = 0.0f;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Weapon")
	float RemainCoolDown = 0.0f;
};
