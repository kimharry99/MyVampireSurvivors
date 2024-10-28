// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MyVamSurCharacter.h"
#include "Engine/DamageEvents.h"
#include "Components/CapsuleComponent.h"
#include "Physics/MyVamSurCollisionChannels.h"
#include "Players/HealthComponent.h"

AMyVamSurCharacter::AMyVamSurCharacter()
{
	SetCanBeDamaged(true);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerCharacter"));

	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	Health->OnDeathStarted.AddDynamic(this, &AMyVamSurCharacter::StartDeath);
}

void AMyVamSurCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	Health->OnDeathStarted.RemoveDynamic(this, &AMyVamSurCharacter::StartDeath);
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
	Health->TakeDamage(ActualDamage);

	return ActualDamage;
}

void AMyVamSurCharacter::StartDeath()
{
	OnCharacterDied.Broadcast();
}
