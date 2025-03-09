// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Enemies/ChasingEnemyAI.h"
#include "Items/PickableItem.h"

AEnemy::AEnemy()
{
	AIControllerClass = AChasingEnemyAI::StaticClass();
	AutoPossessAI = EAutoPossessAI::Spawned;
	bUseControllerRotationYaw = false;

	// Set the collision handling method to always spawn
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));

	GetCharacterMovement()->MaxWalkSpeed = 10.0f;
}

void AEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemy::StartDeath()
{
	Super::StartDeath();

	SpawnDropItem();
	OnEnemyDied.Broadcast(this);
	Destroy();
}

void AEnemy::SpawnDropItem()
{
	if (DropItemClass == nullptr)
	{
		return;
	}

	if (UWorld* World = GetWorld())
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = GetActorRotation();

		World->SpawnActor<APickableItem>(DropItemClass, SpawnLocation, SpawnRotation, SpawnParams);
	}
}
