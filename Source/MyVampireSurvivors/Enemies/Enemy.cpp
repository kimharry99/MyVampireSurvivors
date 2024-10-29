// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Enemies/ChasingEnemyAI.h"
#include "Players/PlayerCharacter.h"
#include "ToroidalMaps/ToroidalNPAComponent.h"

AEnemy::AEnemy()
{
	AIControllerClass = AChasingEnemyAI::StaticClass();
	AutoPossessAI = EAutoPossessAI::Spawned;
	bUseControllerRotationYaw = false;

	// Set the collision handling method to always spawn
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));

	GetCharacterMovement()->MaxWalkSpeed = 10.0f;

	ToroidalNPAComponent = CreateDefaultSubobject<UToroidalNPAComponent>(TEXT("ToroidalNPAComponent"));
}

void AEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (ToroidalNPAComponent)
	{
		ToroidalNPAComponent->AddTickPrerequisiteComponent(GetCharacterMovement());
	}
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	APlayerCharacter* Player = GetWorld()->GetFirstPlayerController()->GetPawn<APlayerCharacter>();
	if (Player)
	{
		Player->AddTickSubsequentToroidalComponent(ToroidalNPAComponent);
	}
}

void AEnemy::StartDeath()
{
	Super::StartDeath();

	OnEnemyDied.Broadcast(this);
	Destroy();
}
