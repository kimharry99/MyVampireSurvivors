// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectPools/PoolableActorInterface.h"
#include "ProjectileWeapon.generated.h"

class UPaperFlipbookComponent;
class UProjectileMovementComponent;
class USphereComponent;
class UToroidalActorComponent;

/**
 * ProjectileWeapon.
 *
 * Projectile will attack a contacted enemy.
 * Usually, the projectile weapon is spawned by a launcher.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API AProjectileWeapon : public AActor, public IPoolableActorInterface
{
	GENERATED_BODY()

public:
	AProjectileWeapon();

public:
	//~IPoolableActorInterface
	virtual void ActivateFromPool() override;
	virtual void DeactivateToPool() override;
	virtual FReturnToPoolDelegate* GetReturnToPoolDelegate() override;
	virtual bool IsInUse() const override;
	//~End of IPoolableActorInterface

	void CopyFromActualClass(TSubclassOf<AProjectileWeapon> ActualClass);
	void SetInitialSpeed(const float InitialSpeed);

	FReturnToPoolDelegate OnReturnToPool;

	/**
	 * Returns the projectile movement component.
	 */
	UProjectileMovementComponent* GetProjectileMovementComponent() const;

protected:
	//~AActor interface
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void LifeSpanExpired() override;
	//~End of AActor interface

private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	float Damage = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> SphereComponent;

	/** The sprite of the projectile. */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPaperFlipbookComponent> SpriteComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Projectile", meta = (AllowPrivateAccess = "true"))
	float LifeTime = 0.5f;

	UPROPERTY(VisibleAnywhere, Category = "ToroidalWorld")
	TObjectPtr<UToroidalActorComponent> ToroidalActorComponent;

	/**
	 * Handle the projectile hit event.
	 */
	UFUNCTION()
	void HandleProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	bool bIsInUse = true;
};
