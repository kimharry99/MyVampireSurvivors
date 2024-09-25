// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Weapon.h"

// Sets default values
AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon::UseWeapon()
{

}

void AWeapon::AttackEnemy(AEnemy* Enemy)
{
	AController* Controller = nullptr;
	if (AActor* ParentActor = GetParentActor())
	{
		Controller = ParentActor->GetInstigatorController();
	}

	Enemy->ReceiveAttack(Damage, Controller);
}

