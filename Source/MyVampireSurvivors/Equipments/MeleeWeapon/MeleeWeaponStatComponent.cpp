// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeWeaponStatComponent.h"

#include "PaperFlipbook.h"
#include "PaperSprite.h"

#include "Equipments/EquipmentCore/EquipmentAnimationData.h"
#include "MyVamSurLogChannels.h"

UMeleeWeaponStatComponent::UMeleeWeaponStatComponent()
	: Super()
{
}

int UMeleeWeaponStatComponent::GetDamage() const
{
	return FMath::RoundToInt(Damage * DamageMultiplier);
}

void UMeleeWeaponStatComponent::AddDamage(int Value)
{
	Damage += Value;
}

void UMeleeWeaponStatComponent::AddDamageMultiplier(float Value)
{
	DamageMultiplier += Value;
}

float UMeleeWeaponStatComponent::GetCooldown() const
{
	float TotalAttackSpeed = AttackSpeed * AttackSpeedMultiplier;
	if (TotalAttackSpeed > 0.0f)
	{
		return 1.0f / TotalAttackSpeed;
	}

	UE_CLOG(GetOwner(), LogMyVamSur, Warning, TEXT("Attack speed is zero %s of %s"), *GetName(), *(GetOwner()->GetName()));
	return 1.0f;
}

void UMeleeWeaponStatComponent::AddAttackSpeed(float Value)
{
	AttackSpeed += Value;
}

void UMeleeWeaponStatComponent::AddAttackSpeedMultiplier(float Value)
{
	AttackSpeedMultiplier += Value;
}

void UMeleeWeaponStatComponent::AddAttackRangeMultiplier(float Value)
{
	HitboxMultiplier += Value;

	OnAnimationSizeChanged.Broadcast(HitboxMultiplier);
}

void UMeleeWeaponStatComponent::Reset()
{
	Damage = 0;
	DamageMultiplier = 1.0f;

	AttackSpeed = 0.0f;
	AttackSpeedMultiplier = 1.0f;

	EquipmentAnimationData.Reset();

	HitboxMultiplier = 1.0f;
}

FEquipmentAnimationData UMeleeWeaponStatComponent::GetAnimationData() const
{
	return EquipmentAnimationData;
}

void UMeleeWeaponStatComponent::SetAnimationData(const FEquipmentAnimationData& NewAnimationData)
{
	if (EquipmentAnimationData == NewAnimationData)
	{
		return;
	}

	EquipmentAnimationData = NewAnimationData;
	
	OnAnimationChanged.Broadcast(EquipmentAnimationData);
}

void UMeleeWeaponStatComponent::AddAnimationChangeEventListener(const FOnAnimationChanged::FDelegate& Listener)
{
	OnAnimationChanged.Add(Listener);
}

void UMeleeWeaponStatComponent::AddAnimationSizeChangeEventListener(const FOnAnimationSizeChanged::FDelegate& Listener)
{
	OnAnimationSizeChanged.Add(Listener);
}

FVector UMeleeWeaponStatComponent::GetHitboxExtent() const
{
	if (!EquipmentAnimationData.Flipbook)
	{
		UE_CLOG(GetOwner(), LogMyVamSur, Warning, TEXT("No Flipbook is set in MeleeWeaponStatComponent of %s"), *(GetOwner()->GetName()));
		return FVector::ZeroVector;
	}

	if (UPaperSprite* HittingFrameSprite = EquipmentAnimationData.Flipbook->GetSpriteAtFrame(EquipmentAnimationData.NotifyKeyFrame))
	{
		return HittingFrameSprite->GetRenderBounds().BoxExtent * HitboxMultiplier;
	}

	UE_CLOG(GetOwner(), LogMyVamSur, Warning, TEXT("Failed to get sprite at frame %d in Flipbook of %s"), EquipmentAnimationData.NotifyKeyFrame, *(GetOwner()->GetName()));
	return FVector::ZeroVector;
}

FVector UMeleeWeaponStatComponent::GetHitboxOffset() const
{
	return EquipmentAnimationData.FlipbookOffset;
}
