// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileLauncherUsageComponent.h"

#include "GameFramework/ProjectileMovementComponent.h"

#include "Equipments/EquipmentCore/StatComponent.h"
#include "IProjectileLauncherStats.h"
#include "MyVamSurLogChannels.h"
#include "ObjectPools/ActorPool.h"
#include "ProjectileSpawnStrategy.h"
#include "ProjectileWeapon.h"

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
};

void UProjectileLauncherUsageComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* World = GetWorld())
	{
		FActorSpawnParameters SpawnParams;
		if (AActor* Owner = GetOwner())
		{
			SpawnParams.Owner = GetOwner();
			SpawnParams.Instigator = GetOwner()->GetInstigator();
		}
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.bHideFromSceneOutliner = true;

		ProjectilePool = World->SpawnActor<AActorPool>(SpawnParams);
		if (ProjectilePool)
		{
			ProjectilePool->SetActorClass(AProjectileWeapon::StaticClass());
		}
	}
}

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
		SpawnProjectile(Stats->GetProjectileWeaponClass(), SpawnTransform, Stats->GetProjectileSpeed());
	}
}

void UProjectileLauncherUsageComponent::HandleCooldownEnded()
{
	OnCooldownEnded.Broadcast();
}

AProjectileWeapon* UProjectileLauncherUsageComponent::SpawnProjectile(TSubclassOf<AProjectileWeapon> ProjectileClass, const FTransform& SpawnTransform, const float InitialSpeed)
{
	check(ProjectileClass);

	if (ProjectilePool)
	{
		if (AActor* SpawnedActor = ProjectilePool->GetPooledActor())
		{
			AProjectileWeapon* SpawnedProjectile = Cast<AProjectileWeapon>(SpawnedActor);
			checkf(SpawnedProjectile, TEXT("ProjectilePool doesn't create AProjectileWeapon type instance."));

			SpawnedProjectile->CopyFromActualClass(ProjectileClass);
			SpawnedProjectile->SetActorTransform(SpawnTransform);
			SpawnedProjectile->SetInitialSpeed(InitialSpeed);

			return SpawnedProjectile;
		}
	}

	return nullptr;
}
