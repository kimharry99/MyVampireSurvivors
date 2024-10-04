// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/AoEWeapon.h"
#include "DrawDebugHelpers.h"
#include "Physics/MyVamSurCollisionChannels.h"

AAoEWeapon::AAoEWeapon()
{
	PlayerPosition = CreateDefaultSubobject<USceneComponent>(TEXT("PlayerPosition"));
	RootComponent = PlayerPosition;

	HitboxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox"));
	HitboxComponent->SetupAttachment(RootComponent);
	HitboxComponent->SetVisibility(false);
	HitboxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WeaponEffectComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("WeaponEffect"));
	WeaponEffectComponent->SetupAttachment(RootComponent);
	WeaponEffectComponent->SetVisibility(false);
	WeaponEffectComponent->SetCollisionProfileName(TEXT("NoCollision"));
	WeaponEffectComponent->SetLooping(false);
}

void AAoEWeapon::BeginPlay()
{
	Super::BeginPlay();

	// Set effect play rate
	if (WeaponEffectComponent->GetFlipbook())
	{
		float EffectDuration = WeaponEffectComponent->GetFlipbookLength();
		if (GetCoolDown() < EffectDuration)
		{
			float EffectPlayingTime = GetCoolDown() * 0.5f;
			float PlayRate = EffectDuration / EffectPlayingTime;
			WeaponEffectComponent->SetPlayRate(PlayRate);
		}
	}
}

AController* AAoEWeapon::GetController() const
{
	if (AActor* ParentActor = GetParentActor())
	{
		return ParentActor->GetInstigatorController();
	}

	return nullptr;
}

float AAoEWeapon::GetWeaponDamage() const
{
	return Damage;
}

void AAoEWeapon::UseEquipment()
{
	Super::UseEquipment();

	PlayWeaponEffect();
}

void AAoEWeapon::PlayWeaponEffect()
{
	if (WeaponEffectComponent->GetFlipbook())
	{
		WeaponEffectComponent->SetVisibility(true);
		WeaponEffectComponent->PlayFromStart();

		float Duration = WeaponEffectComponent->GetFlipbookLength() / WeaponEffectComponent->GetPlayRate();
		FTimerHandle TimerHandle;
		if (UWorld* World = GetWorld())
		{
			World->GetTimerManager().SetTimer(TimerHandle, this, &AAoEWeapon::StopWeaponEffect, Duration, false);
		}
	}
}

void AAoEWeapon::StopWeaponEffect()
{
	WeaponEffectComponent->SetVisibility(false);
	WeaponEffectComponent->Stop();

# if WITH_EDITOR
	HitboxComponent->SetHiddenInGame(true);
	HitboxComponent->SetVisibility(false);
# endif
}

void AAoEWeapon::PerformAoEAttack()
{
	TArray<FOverlapResult> Overlaps;
	DoAoEWeaponTrace(Overlaps);
	AttackHitEnemies(Overlaps);

# if WITH_EDITOR
	HitboxComponent->SetHiddenInGame(false);
	HitboxComponent->SetVisibility(true);
# endif
}

void AAoEWeapon::DoAoEWeaponTrace(TArray<FOverlapResult>& OutOverlaps)
{
	check(HitboxComponent);
	FCollisionShape CollisionShape = FCollisionShape::MakeBox(HitboxComponent->GetScaledBoxExtent());

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	CollisionQueryParams.AddIgnoredActor(GetParentActor());

	UWorld* World = GetWorld();
	check(World);
	World->OverlapMultiByChannel(
		OutOverlaps,
		HitboxComponent->GetComponentLocation(),
		HitboxComponent->GetComponentQuat(),
		TraceChannel_Weapon,
		CollisionShape,
		CollisionQueryParams
	);
}

void AAoEWeapon::AttackHitEnemies(const TArray<FOverlapResult>& Overlaps)
{
	for (const FOverlapResult& OverlapResult : Overlaps)
	{
		AEnemy* OverlappedEnemy = Cast<AEnemy>(OverlapResult.GetActor());
		if (OverlappedEnemy)
		{
			AttackEnemy(OverlappedEnemy);
		}
	}
}
