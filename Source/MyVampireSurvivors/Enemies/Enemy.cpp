// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
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
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	// FIXME: Temporary implementation
	// Set the life time of the enemy
	const float LifeTime = 5.0f;
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(DeathHandle, this, &AEnemy::TriggerDeath, LifeTime, false);
	}
}

void AEnemy::TriggerDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("%s is dead!"), *GetName());
	OnEnemyDied.Broadcast();
	Destroy();
}
