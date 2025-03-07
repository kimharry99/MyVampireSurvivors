// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileWeapon.generated.h"

class UPaperFlipbookComponent;
class UProjectileMovementComponent;
class USphereComponent;
class UToroidalNPAComponent;

/**
 * ProjectileWeapon.
 *
 * Projectile will attack a contacted enemy.
 * Usually, the projectile weapon is spawned by a launcher.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API AProjectileWeapon : public AActor
{
	GENERATED_BODY()

public:
	AProjectileWeapon();

protected:
	//~AActor interface
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~End of AActor interface

private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	float Damage = 10.0f;

public:
	/**
	 * Returns the projectile movement component.
	 */
	UProjectileMovementComponent* GetProjectileMovementComponent() const;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> SphereComponent;

	/** The sprite of the projectile. */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPaperFlipbookComponent> SpriteComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere, Category = "Torus")
	TObjectPtr<UToroidalNPAComponent> ToroidalNPAComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Projectile", meta = (AllowPrivateAccess = "true"))
	float LifeTime = 0.5f;

	/**
	 * Handle the projectile hit event.
	 */
	UFUNCTION()
	void HandleProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
