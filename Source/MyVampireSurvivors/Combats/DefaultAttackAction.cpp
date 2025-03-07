// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultAttackAction.h"

#include "Enemies/Enemy.h"

FDefaultAttackAction::FDefaultAttackAction(const AActor* InInstigator, const int InDamage)
	: Instigator(InInstigator)
	, Damage(InDamage)
{
}

void FDefaultAttackAction::ExecuteAction(AActor* Victim) const
{
	if (AEnemy* AttackedEnemy = Cast<AEnemy>(Victim))
	{
		AttackedEnemy->ReceiveAttack(Damage, GetInstigatorController());
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
