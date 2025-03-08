// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MyVamSurCharacter.h"

#include "Components/CapsuleComponent.h"

#include "Characters/HealthData.h"
#include "Physics/MyVamSurCollisionChannels.h"
#include "ToroidalMaps/ToroidCharacterMovementComponent.h"


AMyVamSurCharacter::AMyVamSurCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer
				.SetDefaultSubobjectClass<UToroidCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	SetCanBeDamaged(true);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerCharacter"));

	HealthData = CreateDefaultSubobject<UHealthData>(TEXT("HealthData"));
	HealthData->OnOutOfHealth.AddDynamic(this, &ThisClass::StartDeath);
}

void AMyVamSurCharacter::BeginPlay()
{
	Super::BeginPlay();

	HealthData->InitializeHealth(DefaultMaxHealth);
}

void AMyVamSurCharacter::ReceiveAttack(float DamageAmount, AController* Attacker)
{
	HealthData->TakeDamage(DamageAmount);
}

void AMyVamSurCharacter::StartDeath()
{
	OnCharacterDied.Broadcast();
}
