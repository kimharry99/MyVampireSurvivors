// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "WeaponInterface.h"
#include "ProjectileWeapon.generated.h"

/**
 * ProjectileWeapon.
 * 
 * Projectile will attack a contacted enemy.
 * Usually, the projectile weapon is spawned by a launcher.
 */
UCLASS()
class MYVAMPIRESURVIVORS_API AProjectileWeapon : public AActor, public IWeaponInterface
{
	GENERATED_BODY()
	
public:	
	AProjectileWeapon();

protected:
	//~AActor interface
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~End of AActor interface

	//~IWeaponInterface interface
	virtual AController* GetController() const override;
	virtual float GetWeaponDamage() const override;
	//~End of IWeaponInterface interface

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

	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> SphereMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon|Projectile", meta = (AllowPrivateAccess = "true"))
	float LifeTime = 0.5f;

	/**
	 * Handle the projectile hit event.
	 */
	UFUNCTION()
	void HandleProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
