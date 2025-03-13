// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/MyVamSurCharacter.h"

#include "Components/CapsuleComponent.h"
#include "PaperFlipbookComponent.h"

#include "Characters/HealthData.h"
#include "Physics/MyVamSurCollisionChannels.h"
#include "ToroidalMaps/ToroidalActorComponent.h"

float AMyVamSurCharacter::GROUND_HEIGHT(50.0f);

AMyVamSurCharacter::AMyVamSurCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetCanBeDamaged(true);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerCharacter"));
	GetCapsuleComponent()->SetCapsuleHalfHeight(GROUND_HEIGHT);

	HealthData = CreateDefaultSubobject<UHealthData>(TEXT("HealthData"));
	HealthData->OnOutOfHealth.AddDynamic(this, &ThisClass::StartDeath);

	ToroidalActorComponent = CreateDefaultSubobject<UToroidalActorComponent>(TEXT("ToroidalActorComponent"));
}

void AMyVamSurCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitialSpriteColor = GetSprite()->GetSpriteColor();
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

void AMyVamSurCharacter::StartBlinking(const float Duration)
{
	if (GetWorld()->GetTimerManager().IsTimerActive(BlinkingTimerHandle))
	{
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(BlinkingTimerHandle, this, &ThisClass::ToggleBlinking, BlinkingInterval, true);
	GetWorld()->GetTimerManager().SetTimer(DurationTimerHandle, this, &ThisClass::StopBlinking, Duration, false);
}

void AMyVamSurCharacter::BlinkOnce()
{
	StartBlinking(BlinkingInterval * 2);
}

void AMyVamSurCharacter::ToggleBlinking()
{
	if (GetSprite())
	{
		bool bCurrentlyVisible = GetSprite()->GetSpriteColor() == InitialSpriteColor;
		GetSprite()->SetSpriteColor(bCurrentlyVisible ? InitialSpriteColor / 2 : InitialSpriteColor);
	}
}

void AMyVamSurCharacter::StopBlinking()
{
	GetWorld()->GetTimerManager().ClearTimer(BlinkingTimerHandle);
	if (GetSprite())
	{
		GetSprite()->SetSpriteColor(InitialSpriteColor);
	}
}
