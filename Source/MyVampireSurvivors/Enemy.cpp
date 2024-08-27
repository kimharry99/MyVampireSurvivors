// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "ChasingEnemyAI.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemy::AEnemy()
{
	AIControllerClass = AChasingEnemyAI::StaticClass();
	bUseControllerRotationYaw = false;
	
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ToroidalActor"));

	GetCharacterMovement()->MaxWalkSpeed = 10.0f;
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
}
