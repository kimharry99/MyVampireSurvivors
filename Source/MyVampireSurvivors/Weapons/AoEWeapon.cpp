// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/AoEWeapon.h"
#include "DrawDebugHelpers.h"

AAoEWeapon::AAoEWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	AttackRangeComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackRangeComponent"));
	AttackRangeComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackRangeComponent->bHiddenInGame = true;
	RootComponent = AttackRangeComponent;
}

void AAoEWeapon::UseWeapon()
{
	Super::UseWeapon();

	check(AttackRangeComponent);
	FCollisionShape CollisionShape = FCollisionShape::MakeBox(AttackRangeComponent->GetScaledBoxExtent());

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	CollisionQueryParams.AddIgnoredActor(GetParentActor());

	UWorld* World = GetWorld();
	check(World);
	TArray<FOverlapResult> OverlapResults;
	bool bOverlapped = World->OverlapMultiByChannel(
		OverlapResults,
		GetActorLocation(),
		GetActorQuat(),
		ECollisionChannel::ECC_Pawn,
		CollisionShape,
		CollisionQueryParams
	);

	DrawDebugBox(
		World,
		GetActorLocation(),
		AttackRangeComponent->GetScaledBoxExtent(),
		FQuat::Identity,
		FColor::Red,
		false,
		0.5f
	);

	if (bOverlapped)
	{
		for (const FOverlapResult& OverlapResult : OverlapResults)
		{
			AEnemy* OverlappedEnemy = Cast<AEnemy>(OverlapResult.GetActor());
			if (OverlappedEnemy)
			{
				AttackEnemy(OverlappedEnemy);
			}
		}
	}
}

void AAoEWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AttackCoolDown -= DeltaTime;
	if (AttackCoolDown <= 0.0f)
	{
		UseWeapon();
		AttackCoolDown = 1.0f;
	}
}