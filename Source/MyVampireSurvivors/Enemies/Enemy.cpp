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
}

void AEnemy::Die()
{
	Super::Die();

	Destroy();
}
