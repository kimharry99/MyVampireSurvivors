// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MyVamSurCharacter.h"
#include "Engine/DamageEvents.h"
#include "Components/CapsuleComponent.h"
#include "Physics/MyVamSurCollisionChannels.h"
#include "Characters/HealthComponent.h"


AMyVamSurCharacter::AMyVamSurCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetCanBeDamaged(true);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerCharacter"));

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnDeathStarted.AddDynamic(this, &AMyVamSurCharacter::StartDeath);
}

void AMyVamSurCharacter::ReceiveAttack(float DamageAmount, AController* Attacker)
{
	HealthComponent->TakeDamage(DamageAmount);
}

void AMyVamSurCharacter::StartDeath()
{
	OnCharacterDied.Broadcast();
}
