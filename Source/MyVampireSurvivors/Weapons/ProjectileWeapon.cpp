// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileWeapon.h"
#include "UObject/ConstructorHelpers.h"
#include "MyVamSurLogChannels.h"
#include "Enemies/Enemy.h"

AProjectileWeapon::AProjectileWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->InitSphereRadius(10.0f);
	SphereComponent->SetSimulatePhysics(true);
	SphereComponent->SetEnableGravity(false);

	SphereComponent->SetNotifyRigidBodyCollision(true);
	SphereComponent->SetGenerateOverlapEvents(false);
	SphereComponent->SetCollisionProfileName(TEXT("Projectile"));
	SphereComponent->OnComponentHit.AddDynamic(this, &AProjectileWeapon::HandleProjectileHit);
	RootComponent = SphereComponent;

	SphereMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMeshComponent"));
	SphereMeshComponent->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (SphereMesh.Succeeded())
	{
		SphereMeshComponent->SetStaticMesh(SphereMesh.Object);
		SphereMeshComponent->SetRelativeScale3D(FVector(SphereComponent->GetUnscaledSphereRadius() / 50.0f));
		SphereMeshComponent->SetGenerateOverlapEvents(false);
		SphereMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
		SphereMeshComponent->SetEnableGravity(false);
	}

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	ProjectileMovementComponent->InitialSpeed = 1000.0f;
	ProjectileMovementComponent->MaxSpeed = 1000.0f;
}

void AProjectileWeapon::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(LifeTime);
}

void AProjectileWeapon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	SphereComponent->OnComponentHit.RemoveAll(this);
}

void AProjectileWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

AController* AProjectileWeapon::GetController() const
{
	// Owner will be launcher of the projectile
	if(AActor* Launcher = GetOwner())
	{
		return Launcher->GetInstigatorController();
	}
	return nullptr;
}

float AProjectileWeapon::GetWeaponDamage() const
{
	return Damage;
}

UProjectileMovementComponent* AProjectileWeapon::GetProjectileMovementComponent() const
{
	return ProjectileMovementComponent;
}

void AProjectileWeapon::HandleProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	// If the projectile hits an enemy, attack enemy.
	if (OtherActor->IsA<AEnemy>())
	{
		AEnemy* Enemy = Cast<AEnemy>(OtherActor);
		AttackEnemy(Enemy);
		Destroy();
	}
}
