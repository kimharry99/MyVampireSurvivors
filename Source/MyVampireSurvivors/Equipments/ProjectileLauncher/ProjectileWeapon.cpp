// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileWeapon.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PaperFlipbookComponent.h"

#include "Combats/DefaultAttackAction.h"
#include "Combats/CombatManager.h"
#include "ToroidalMaps/ToroidalNPAComponent.h"
#include "MyVamSurLogChannels.h"

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

	ToroidalNPAComponent = CreateDefaultSubobject<UToroidalNPAComponent>(TEXT("ToroidalNPAComponent"));
}

void AProjectileWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (ToroidalNPAComponent)
	{
		ToroidalNPAComponent->AddTickPrerequisiteComponent(ProjectileMovementComponent);
	}
}

void AProjectileWeapon::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(LifeTime);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn)
	{
		ToroidalNPAComponent->AddTickPrerequisiteActor(PlayerPawn);
	}
}

void AProjectileWeapon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	SphereComponent->OnComponentHit.RemoveAll(this);
}

UProjectileMovementComponent* AProjectileWeapon::GetProjectileMovementComponent() const
{
	return ProjectileMovementComponent;
}

void AProjectileWeapon::HandleProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	FDefaultAttackAction DefaultAttack(GetInstigatorController(), Damage);
	FCombatManager::PerformTargetedAttack(OtherActor, DefaultAttack);
	
	Destroy();
}
