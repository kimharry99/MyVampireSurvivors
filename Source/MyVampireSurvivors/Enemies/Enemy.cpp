// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyVamSurLogChannels.h"
#include "ChasingEnemyAI.h"

AEnemy::AEnemy()
{
	AIControllerClass = AChasingEnemyAI::StaticClass();
	AutoPossessAI = EAutoPossessAI::Spawned;
	bUseControllerRotationYaw = false;

	// Set the collision handling method to always spawn
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ToroidalActor"));

	GetCharacterMovement()->MaxWalkSpeed = 10.0f;

	const float DefaultHealthPoint = 5.0f;
	SetHealthPoint(DefaultHealthPoint);
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	// FIXME: Temporary implementation
	// Set the life time of the enemy
	const float DamagedPeriod = 1.0f;
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(SelfHarmHandle, this, &AEnemy::PerformSelfHarm, DamagedPeriod, false);
	}
}

void AEnemy::Die()
{
	Super::Die();

	Destroy();
}

void AEnemy::PerformSelfHarm()
{
	const float DamageAmount = 1.0f;
	ReceiveAttack(DamageAmount, GetController());

	const float DamagedPeriod = 1.0f;
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(SelfHarmHandle, this, &AEnemy::PerformSelfHarm, DamagedPeriod, false);
	}
}
