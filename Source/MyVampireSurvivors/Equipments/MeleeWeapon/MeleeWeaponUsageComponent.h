// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Equipments/EquipmentCore/UsageComponent.h"
#include "MeleeWeaponUsageComponent.generated.h"

class IMeleeWeaponStats;
class UPaperFlipbookComponent;
class UMyFlipbookNotifierComponent;

/**
 * 
 */
UCLASS()
class MYVAMPIRESURVIVORS_API UMeleeWeaponUsageComponent : public UUsageComponent
{
	GENERATED_BODY()

public:
	UMeleeWeaponUsageComponent();

public:
	FSimpleMulticastDelegate OnCooldownEnded;

private:
	//~UUsageComponent interface
	virtual void ExecuteUseInternal(UStatComponent* StatComponent, UPaperFlipbookComponent* FlipbookComponent, UMyFlipbookNotifierComponent* NotifierComponent) override;
	//~End of UUsageComponent interface

	void UpdateCoolTime(IMeleeWeaponStats* Stats);

	void PlayAnimation(UPaperFlipbookComponent* FlipbookComponent, const IMeleeWeaponStats* Stats);
	void StopAnimation(TWeakObjectPtr<UPaperFlipbookComponent> FlipbookComponent);

	void ReserveAttack(UStatComponent* StatComponent, UMyFlipbookNotifierComponent* NotifierComponent);

	void PerformAttack(TWeakObjectPtr<UStatComponent> Stats);

	void HandleCooldownEnded();

private:
	FTimerHandle CooldownHandle;
	FTimerHandle AnimationTimerHandle;
};
