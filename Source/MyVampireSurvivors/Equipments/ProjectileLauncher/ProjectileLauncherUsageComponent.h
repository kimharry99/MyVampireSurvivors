// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Equipments/EquipmentCore/UsageComponent.h"
#include "ProjectileLauncherUsageComponent.generated.h"

class AActorPool;
class AProjectileWeapon;
class IProjectileLauncherStats;

/**
 * 
 */
UCLASS(ClassGroup = Equipment)
class MYVAMPIRESURVIVORS_API UProjectileLauncherUsageComponent : public UUsageComponent
{
	GENERATED_BODY()

public:
	FSimpleMulticastDelegate OnCooldownEnded;

protected:
	//~UActorComponent interface
	virtual void BeginPlay() override;
	//~End of UActorComponent interface

private:
	//~UUsageComponent interface
	virtual void ExecuteUseInternal(UStatComponent* StatComponent) override;
	//~End of UUsageComponent interface

	FTimerHandle CooldownHandle;

	void UpdateCoolTime(IProjectileLauncherStats* Stats);
	void Launch(IProjectileLauncherStats* Stats);

	void HandleCooldownEnded();

	UPROPERTY()
	TObjectPtr<AActorPool> ProjectilePool;
	
	AProjectileWeapon* SpawnProjectile(TSubclassOf<AProjectileWeapon> ProjectileClass, const FTransform& SpawnTransform, const float InitialSpeed);
};
