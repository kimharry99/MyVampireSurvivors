// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileLauncherUsageComponent.h"

#include "GameFramework/ProjectileMovementComponent.h"

#include "Equipments/EquipmentCore/StatComponent.h"
#include "IProjectileLauncherStats.h"
#include "ProjectileWeapon.h"
#include "ProjectileSpawnStrategy.h"
#include "MyVamSurLogChannels.h"

namespace
{
	TArray<FTransform> ComputeSpawnTransforms(const UProjectileSpawnStrategy* SpawnStrategy, const AActor* OriginActor, const int Count)
	{
		if (!SpawnStrategy || !OriginActor)
		{
			return TArray<FTransform>();
		}

		return SpawnStrategy->GetSpawnTransform(OriginActor->GetActorTransform(), Count);
	}

	AProjectileWeapon* SpawnProjectile(UWorld* World, AActor* Owner, TSubclassOf<AProjectileWeapon> ProjectileClass, const FTransform& SpawnTransform)
	{
		if (!World || !Owner || !ProjectileClass)
		{
			return nullptr;
		}

		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = Owner;
		SpawnInfo.Instigator = Owner->GetInstigator();

		return World->SpawnActor<AProjectileWeapon>(ProjectileClass, SpawnTransform, SpawnInfo);
	}

	void InitializeProjectileMovement(UProjectileMovementComponent* MovementComponent, const float Speed)
	{
		if (!MovementComponent)
		{
			return;
		}

		const FVector Direction = MovementComponent->Velocity.GetSafeNormal();
		if (!Direction.IsZero())
		{
			MovementComponent->Velocity *= Direction * Speed;
		}
	}
};

void UProjectileLauncherUsageComponent::ExecuteUseInternal(UStatComponent* StatComponent)
{
	if (IProjectileLauncherStats* ProjectileLauncherStats = Cast<IProjectileLauncherStats>(StatComponent))
	{
		Launch(ProjectileLauncherStats);
		UpdateCoolTime(ProjectileLauncherStats);
	}
}

void UProjectileLauncherUsageComponent::UpdateCoolTime(IProjectileLauncherStats* Stats)
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(
			CooldownHandle,
			FTimerDelegate::CreateUObject(this, &ThisClass::HandleCooldownEnded),
			Stats->GetCooldown(),
			false
		);
	}
}

void UProjectileLauncherUsageComponent::Launch(IProjectileLauncherStats* Stats)
{
	if (!Stats)
	{
		return;
	}

	TArray<FTransform> SpawnTransforms = ComputeSpawnTransforms(Stats->GetSpawnStrategy(), GetOwner(), Stats->GetProjectileCount());
	for (const auto& SpawnTransform : SpawnTransforms)
	{
		if (AProjectileWeapon* Projectile = SpawnProjectile(GetWorld(), GetOwner(), Stats->GetProjectileWeaponClass(), SpawnTransform))
		{
			InitializeProjectileMovement(Projectile->GetProjectileMovementComponent(), Stats->GetProjectileSpeed());
		}
	}
}

void UProjectileLauncherUsageComponent::HandleCooldownEnded()
{
	OnCooldownEnded.Broadcast();
}
