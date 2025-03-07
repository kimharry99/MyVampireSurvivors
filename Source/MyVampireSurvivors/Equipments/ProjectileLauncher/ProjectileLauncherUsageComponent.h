// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Equipments/EquipmentCore/UsageComponent.h"
#include "ProjectileLauncherUsageComponent.generated.h"

class IProjectileLauncherStats;
class UProjectileSpawnStrategy;

/**
 * 
 */
UCLASS(ClassGroup = Equipment)
class MYVAMPIRESURVIVORS_API UProjectileLauncherUsageComponent : public UUsageComponent
{
	GENERATED_BODY()

public:
	FSimpleMulticastDelegate OnCooldownEnded;

private:
	//~UUsageComponent interface
	virtual void ExecuteUseInternal(UStatComponent* StatComponent) override;
	//~End of UUsageComponent interface

	FTimerHandle CooldownHandle;

	void UpdateCoolTime(IProjectileLauncherStats* Stats);
	void Launch(IProjectileLauncherStats* Stats);

	void HandleCooldownEnded();
};
