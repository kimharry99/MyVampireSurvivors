// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "PaperFlipbookComponent.h"
#include "PaperZDAnimationComponent.h"

#include "Characters/HealthData.h"
#include "MyVamSurLogChannels.h"
#include "Enemies/ChasingEnemyAI.h"
#include "Enemies/EmptyEnemyAnimInstance.h"
#include "Enemies/EnemyCombatComponent.h"
#include "GameModes/MyVamSurGameMode.h"
#include "Spawner/Spawner.h"
#include "Items/PickableItem.h"

AEnemy::AEnemy(const FObjectInitializer& ObjectInitializer)
{
	AIControllerClass = AChasingEnemyAI::StaticClass();
	AutoPossessAI = EAutoPossessAI::Spawned;
	bUseControllerRotationYaw = false;

	// Set the collision handling method to always spawn
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));

	UPaperZDAnimationComponent* AnimComp = GetAnimationComponent();
	check(AnimComp);
	AnimComp->SetAnimInstanceClass(UEmptyEnemyAnimInstance::StaticClass());

	GetCharacterMovement()->MaxWalkSpeed = 10.0f;

	CombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>(TEXT("CombatComponent"));
}

void AEnemy::ActivateFromPool()
{
	bIsInUse = true;
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);

	if (AController* ControllerActor = GetController())
	{
		ControllerActor->SetActorHiddenInGame(false);
		ControllerActor->SetActorTickEnabled(true);
	}
}

void AEnemy::DeactivateToPool()
{
	bIsInUse = false;
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);

	if (AController* ControllerActor = GetController())
	{
		ControllerActor->SetActorHiddenInGame(true);
		ControllerActor->SetActorTickEnabled(false);
	}
}

bool AEnemy::IsInUse() const
{
	return bIsInUse;
}

FReturnToPoolDelegate* AEnemy::GetReturnToPoolDelegate()
{
	return &OnReturnToPool;
}

void AEnemy::CopyFromActualClass(TSubclassOf<AEnemy> ActualClass)
{
	check(ActualClass);

	const AEnemy* EnemyCDO = ActualClass->GetDefaultObject<AEnemy>();
	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	const UCapsuleComponent* CDOCapsuleComp = EnemyCDO->GetCapsuleComponent();
	if (CapsuleComp && CDOCapsuleComp)
	{
		CapsuleComp->SetCapsuleHalfHeight(CDOCapsuleComp->GetUnscaledCapsuleHalfHeight());
		CapsuleComp->SetCapsuleRadius(CDOCapsuleComp->GetUnscaledCapsuleRadius());
	}

	UPaperFlipbookComponent* SpriteComp = GetSprite();
	UPaperFlipbookComponent* CDOSpriteComp = EnemyCDO->GetSprite();
	if (SpriteComp && CDOSpriteComp)
	{
		SpriteComp->SetRelativeRotation(CDOSpriteComp->GetRelativeRotation());
		SpriteComp->SetFlipbook(CDOSpriteComp->GetFlipbook());
		SpriteComp->SetSpriteColor(CDOSpriteComp->GetSpriteColor());
	}

	UPaperZDAnimationComponent* AnimComp = GetAnimationComponent();
	const UPaperZDAnimationComponent* CDOAnimComp = EnemyCDO->GetAnimationComponent();
	if (AnimComp && CDOAnimComp)
	{
		AnimComp->SetAnimInstanceClass(CDOAnimComp->GetAnimInstanceClass());
	}

	UCharacterMovementComponent* MovementComp = GetCharacterMovement();
	const UCharacterMovementComponent* CDOMovementComp = EnemyCDO->GetCharacterMovement();
	if (MovementComp && CDOMovementComp)
	{
		MovementComp->MaxWalkSpeed = CDOMovementComp->MaxWalkSpeed;
	}

	GetHealthData()->InitializeHealth(EnemyCDO->GetDefaultMaxHealth());

	DropItemClass = EnemyCDO->DropItemClass;
}

void AEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* World = GetWorld())
	{
		if (AMyVamSurGameMode* GameMode = World->GetAuthGameMode<AMyVamSurGameMode>())
		{
			DropItemSpawner = GameMode->GetSpawner();
		}
	}
}

void AEnemy::StartDeath()
{
	Super::StartDeath();

	SpawnDropItem();
	OnEnemyDied.Broadcast(this);
	OnWaveActorDestroyed.Broadcast(this);
	if (OnReturnToPool.IsBound())
	{
		OnReturnToPool.Execute(this);
	}
	DeactivateToPool();
}

FOnWaveActorDestroyedDelegate* AEnemy::GetOnWaveActorDestroyedDelegate()
{
	return &OnWaveActorDestroyed;
}

void AEnemy::SpawnDropItem()
{
	if (DropItemClass == nullptr)
	{
		return;
	}

	if (DropItemSpawner)
	{
		DropItemSpawner->SpawnActor(DropItemClass, FTransform(GetActorRotation(), GetActorLocation()));
	}
	else
	{
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
}
