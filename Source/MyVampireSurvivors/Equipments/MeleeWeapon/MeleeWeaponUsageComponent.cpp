// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeWeaponUsageComponent.h"

#include "PaperFlipbookComponent.h"

#include "Combats/CombatManager.h"
#include "Combats/DefaultAttackAction.h"
#include "Enemies/Enemy.h"
#include "Equipments/EquipmentCore/EquipmentAnimationData.h"
#include "Equipments/EquipmentCore/MyFlipbookNotifierComponent.h"
#include "Equipments/EquipmentCore/StatComponent.h"
#include "IMeleeWeaponStats.h"
#include "MyVamSurLogChannels.h"
#include "Physics/CollisionQueryInfo.h"
#include "Physics/MyVamSurCollisionChannels.h"

//////////////////////////////////////////////////////////////////////
// UMeleeWeaponUsageComponent
UMeleeWeaponUsageComponent::UMeleeWeaponUsageComponent()
	: Super()
{
}

void UMeleeWeaponUsageComponent::ExecuteUseInternal(UStatComponent* StatComponent, UPaperFlipbookComponent* FlipbookComponent, UMyFlipbookNotifierComponent* NotifierComponent)
{
	if (IMeleeWeaponStats* MeleeWeaponStats = Cast<IMeleeWeaponStats>(StatComponent))
	{
		PlayAnimation(FlipbookComponent, MeleeWeaponStats);
		ReserveAttack(StatComponent, NotifierComponent);

		UpdateCoolTime(MeleeWeaponStats);
	}
}

void UMeleeWeaponUsageComponent::UpdateCoolTime(IMeleeWeaponStats* Stats)
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

void UMeleeWeaponUsageComponent::PlayAnimation(UPaperFlipbookComponent* FlipbookComponent, const IMeleeWeaponStats* Stats)
{
	if (!FlipbookComponent || !FlipbookComponent->GetFlipbook())
	{
		return;
	}

	const float AnimationDuration = FlipbookComponent->GetFlipbookLength();
	const float PlayingTime = Stats->GetCooldown() * 0.5f;
	const float PlayRate = AnimationDuration / PlayingTime;

	FlipbookComponent->SetPlayRate(PlayRate);
	FlipbookComponent->SetVisibility(true);
	FlipbookComponent->PlayFromStart();

	if (UWorld* World = GetWorld())
	{
		TWeakObjectPtr<UMeleeWeaponUsageComponent> WeakThis(this);
		TWeakObjectPtr<UPaperFlipbookComponent> WeakFlipbookComponent(FlipbookComponent);
		World->GetTimerManager().SetTimer(
			AnimationTimerHandle,
			FTimerDelegate::CreateWeakLambda(
				WeakThis.Get(),
				[WeakThis, WeakFlipbookComponent]
				{
					WeakThis->StopAnimation(WeakFlipbookComponent);
				}
			),
			PlayingTime,
			false
		);
	}
}

void UMeleeWeaponUsageComponent::StopAnimation(TWeakObjectPtr<UPaperFlipbookComponent> FlipbookComponent)
{
	if (!FlipbookComponent.IsValid())
	{
		return;
	}

	FlipbookComponent->SetVisibility(false);
	FlipbookComponent->Stop();
}

void UMeleeWeaponUsageComponent::ReserveAttack(UStatComponent* StatComponent, UMyFlipbookNotifierComponent* NotifierComponent)
{
	// Create weak pointers for safety in the delegate
	TWeakObjectPtr<UMeleeWeaponUsageComponent> WeakThis(this);
	TWeakObjectPtr<UStatComponent> WeakStats(StatComponent);

	// The lambda captures the weak pointers to safely call PerformAttack_Deprecated later.
	NotifierComponent->AddOnceEventListener(
		FOnFrameNotify::FDelegate::CreateWeakLambda(
			WeakThis.Get(),
			[WeakThis, WeakStats]()
			{
				WeakThis->PerformAttack(WeakStats);
			}
		)
	);
}

void UMeleeWeaponUsageComponent::PerformAttack(TWeakObjectPtr<UStatComponent> Stats)
{
	if (!Stats.IsValid())
	{
		return;
	}

	if (IMeleeWeaponStats* MeleeWeaponStats = Cast<IMeleeWeaponStats>(Stats))
	{
		if (AActor* Owner = GetOwner())
		{
			FCollisionQueryInfo Info(
				FCollisionShape::MakeBox(MeleeWeaponStats->GetHitboxExtent()),
				Owner->GetActorQuat(),
				Owner->GetActorLocation() + Owner->GetActorQuat().RotateVector(MeleeWeaponStats->GetHitboxOffset()),
				TraceChannel_Weapon
			);
			FDefaultAttackAction WeaponAction(Owner, MeleeWeaponStats->GetDamage(), AEnemy::StaticClass());

			FCombatManager::PerformAoEAttack(Info, WeaponAction);
		}
	}
}

void UMeleeWeaponUsageComponent::HandleCooldownEnded()
{
	OnCooldownEnded.Broadcast();
}
