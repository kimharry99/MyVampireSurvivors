// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileWeapon.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PaperFlipbookComponent.h"

#include "Combats/CombatManager.h"
#include "Combats/DefaultAttackAction.h"
#include "Enemies/Enemy.h"
#include "MyVamSurLogChannels.h"
#include "ToroidalMaps/ToroidalActorComponent.h"

AProjectileWeapon::AProjectileWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->InitSphereRadius(10.0f);
	RootComponent = SphereComponent;

	SphereComponent->SetSimulatePhysics(true);
	SphereComponent->SetEnableGravity(false);
	SphereComponent->SetNotifyRigidBodyCollision(true);
	SphereComponent->SetGenerateOverlapEvents(false);
	SphereComponent->SetCollisionProfileName(TEXT("Projectile"));
	SphereComponent->OnComponentHit.AddDynamic(this, &AProjectileWeapon::HandleProjectileHit);

	SpriteComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	SpriteComponent->SetupAttachment(RootComponent);
	SpriteComponent->SetGenerateOverlapEvents(false);
	SpriteComponent->SetCollisionProfileName(TEXT("NoCollision"));
	SpriteComponent->SetEnableGravity(false);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	ProjectileMovementComponent->InitialSpeed = 1000.0f;
	ProjectileMovementComponent->MaxSpeed = 5000.0f;

	ToroidalActorComponent = CreateDefaultSubobject<UToroidalActorComponent>(TEXT("ToroidalNPAComponent"));
}

void AProjectileWeapon::ActivateFromPool()
{
	bIsInUse = true;
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);

	SetLifeSpan(LifeTime);
}

void AProjectileWeapon::DeactivateToPool()
{
	bIsInUse = false;

	if (ProjectileMovementComponent)
	{
		ProjectileMovementComponent->StopMovementImmediately();
	}
	if (SphereComponent->IsSimulatingPhysics())
	{
		SphereComponent->SetPhysicsLinearVelocity(FVector::ZeroVector);
		SphereComponent->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	}

	SetLifeSpan(-1.0f); // Clear TimerHandle_LifeSpanExpired

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

FReturnToPoolDelegate* AProjectileWeapon::GetReturnToPoolDelegate()
{
	return &OnReturnToPool;
}

bool AProjectileWeapon::IsInUse() const
{
	return bIsInUse;
}

void AProjectileWeapon::CopyFromActualClass(TSubclassOf<AProjectileWeapon> ActualClass)
{
	check(ActualClass);
	
	const AProjectileWeapon* ProjectileCDO = ActualClass->GetDefaultObject<AProjectileWeapon>();
	if (ensure(ProjectileCDO))
	{
		Damage = ProjectileCDO->Damage;

		UPaperFlipbookComponent* CDOSpriteComp = ProjectileCDO->SpriteComponent;
		if (SpriteComponent && CDOSpriteComp)
		{
			SpriteComponent->SetRelativeScale3D(CDOSpriteComp->GetRelativeScale3D());
			SpriteComponent->SetFlipbook(CDOSpriteComp->GetFlipbook());
		}
	}
}

void AProjectileWeapon::SetInitialSpeed(const float InitialSpeed)
{
	if (!ProjectileMovementComponent)
	{
		return;
	}

	if (SphereComponent)
	{
		FVector Velocity = FVector::ForwardVector;
		Velocity = SphereComponent->GetComponentToWorld().TransformVectorNoScale(Velocity);
		Velocity = InitialSpeed * Velocity;

		ProjectileMovementComponent->Velocity = Velocity;
		ProjectileMovementComponent->UpdateComponentVelocity();
		if (SphereComponent->IsSimulatingPhysics())
		{
			SphereComponent->SetPhysicsLinearVelocity(Velocity);
		}
	}
}

UProjectileMovementComponent* AProjectileWeapon::GetProjectileMovementComponent() const
{
	return ProjectileMovementComponent;
}

void AProjectileWeapon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	SphereComponent->OnComponentHit.RemoveAll(this);
}

void AProjectileWeapon::LifeSpanExpired()
{
	if (OnReturnToPool.IsBound())
	{
		OnReturnToPool.Execute(this);
	}
	else
	{
		Super::LifeSpanExpired();
	}
}

void AProjectileWeapon::HandleProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	FDefaultAttackAction DefaultAttack(GetInstigatorController(), Damage, AEnemy::StaticClass());
	FCombatManager::PerformTargetedAttack(OtherActor, DefaultAttack);

	if (OnReturnToPool.IsBound())
	{
		OnReturnToPool.Execute(this);
	}
	else
	{
		Destroy();
	}
}
