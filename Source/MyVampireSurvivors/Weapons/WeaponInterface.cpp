// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/WeaponInterface.h"

void IWeaponInterface::AttackEnemy(AEnemy* AttackedEnemy)
{
	AController* Controller = GetController();
	float Damage = GetWeaponDamage();
	AttackedEnemy->ReceiveAttack(Damage, Controller);
}
