// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MyVamSurCharacter.h"
#include "Engine/DamageEvents.h"
#include "Components/CapsuleComponent.h"
#include "Physics/MyVamSurCollisionChannels.h"

AMyVamSurCharacter::AMyVamSurCharacter()
{
	SetCanBeDamaged(true);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerCharacter"));
}

void AMyVamSurCharacter::SetHealthPoint(float NewHealthPoint)
{
	HealthPoint = NewHealthPoint;
}

void AMyVamSurCharacter::ReceiveAttack(float DamageAmount, AController* Attacker)
{
	FDamageEvent DamageEvent;
	AActor* DamageCauser = Attacker ? Attacker->GetPawn() : nullptr;
	TakeDamage(DamageAmount, DamageEvent, Attacker, DamageCauser);
}

float AMyVamSurCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	HealthPoint -= ActualDamage;
	if (HealthPoint <= 0)
	{
		Die();
	}

	return ActualDamage;
}

void AMyVamSurCharacter::Die()
{
	OnCharacterDied.Broadcast();
}
