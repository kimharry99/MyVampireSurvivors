// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCombatComponent.h"

#include "Combats/CombatManager.h"
#include "Combats/DefaultAttackAction.h"
#include "Players/PlayerCharacter.h"
#include "MyVamSurLogChannels.h"

UEnemyCombatComponent::UEnemyCombatComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UEnemyCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!HitPrimitiveComponent)
	{
		FindHitPrimitiveComponentFromOwnerRoot();
	}
	if (HitPrimitiveComponent)
	{
		HitPrimitiveComponent->OnComponentHit.AddDynamic(this, &ThisClass::HandleEnemyHit);
	}
}

void UEnemyCombatComponent::FindHitPrimitiveComponentFromOwnerRoot()
{
	if (AActor* Actor = GetOwner())
	{
		HitPrimitiveComponent = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
	}
}

void UEnemyCombatComponent::HandleEnemyHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (AActor* Owner = GetOwner())
	{
		FDefaultAttackAction AttackAction(Owner->GetInstigatorController(), Damage, APlayerCharacter::StaticClass());
		FCombatManager::PerformTargetedAttack(OtherActor, AttackAction);
	}
}
