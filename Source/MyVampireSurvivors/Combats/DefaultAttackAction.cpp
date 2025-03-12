// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultAttackAction.h"

#include "Characters/MyVamSurCharacter.h"
#include "Enemies/Enemy.h"

FDefaultAttackAction::FDefaultAttackAction(const AActor* InInstigator, const int InDamage, UClass* InTargetClass)
	: Instigator(InInstigator)
	, Damage(InDamage)
	, TargetClass(InTargetClass)
{
}

void FDefaultAttackAction::ExecuteAction(AActor* Victim) const
{
	if (Victim && Victim->GetClass()->IsChildOf(TargetClass))
	{
		if (AMyVamSurCharacter* AttackedCharacter = Cast<AMyVamSurCharacter>(Victim))
		{
			AttackedCharacter->ReceiveAttack(Damage, GetInstigatorController());
		}
	}
}

const AActor* FDefaultAttackAction::GetInstigator() const
{
	if (!Instigator.IsValid())
	{
		return nullptr;
	}

	return Instigator.Get();
}

AController* FDefaultAttackAction::GetInstigatorController() const
{
	if (!Instigator.IsValid())
	{
		return nullptr;
	}

	return Instigator->GetInstigatorController();
}
